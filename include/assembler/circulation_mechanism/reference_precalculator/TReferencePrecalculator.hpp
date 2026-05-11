#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "TReferencePrecalculatorId.hpp"
#include "TReferencePrecalculationStatus.hpp"
#include "TReferenceCandidate.hpp"
#include "policies/TReferenceSupplyPolicy.hpp"
#include "handles/TIngressAccessRef.hpp"
#include "handles/TDispatchAccessRef.hpp"
#include "reports/TReferencePrecalculationReport.hpp"
#include "reports/TReferenceSupplyInterruptionReport.hpp"
#include "reports/TReferenceCandidateRejectionReport.hpp"
#include "views/TReferenceSupplyView.hpp"
#include "views/TIngressReferenceSupplyView.hpp"
#include "views/TDispatchReferenceSupplyView.hpp"

/*
    TReferencePrecalculator.hpp

    Delivery:
        CME-REFPREC-PROD-W01 — Production Locating And Ref Supply Contract

    Current responsibility:
        Production-grade locating and next-ref supply engine.

    Expected registry/container interface:
        registry.try_get(TContainerRegistryIndex) -> const Container*
        registry.generation() -> uint64
        container.state() -> TContainerState
        container.find_first_ingress_writable_slot() -> TSlotIndex
        container.find_first_dispatch_ready_slot() -> TSlotIndex

    Production capabilities:
        - consumes candidates from waiting lists,
        - resolves registry indices,
        - checks container state,
        - selects ingress/dispatch slot,
        - produces TIngressAccessRef and TDispatchAccessRef,
        - stores fixed-capacity ref pools,
        - pops next ingress/dispatch ref,
        - emits candidate rejection reports,
        - emits supply/interruption/precalculation reports.

    Non-ownership:
        - Does not mutate registry, container, or slot.
        - Does not place payload.
        - Does not expose dispatch.
        - Does not inspect envelope content.
        - Does not execute bridge behavior.
*/
namespace assembler {
namespace circulation_mechanism {

template <std::size_t IngressPoolCapacity, std::size_t DispatchPoolCapacity>
class TReferencePrecalculator final {
public:
    static_assert(IngressPoolCapacity > 0U, "Ingress pool capacity must be > 0");
    static_assert(DispatchPoolCapacity > 0U, "Dispatch pool capacity must be > 0");

    constexpr TReferencePrecalculator(TReferencePrecalculatorId id, TReferenceSupplyPolicy policy, std::uint64_t profile_generation = 1U) noexcept
        : id_(id), policy_(policy), profile_generation_(profile_generation) {
        status_ = is_valid() ? TReferencePrecalculationStatus::ready : TReferencePrecalculationStatus::invariant_violation;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && policy_.is_valid() && profile_generation_ > 0U;
    }

    [[nodiscard]] constexpr std::uint32_t ingress_ready_count() const noexcept { return ingress_count_; }
    [[nodiscard]] constexpr std::uint32_t dispatch_ready_count() const noexcept { return dispatch_count_; }
    [[nodiscard]] constexpr TReferencePrecalculationStatus status() const noexcept { return status_; }

    [[nodiscard]] constexpr TReferenceSupplyView supply_view() const noexcept {
        return TReferenceSupplyView{id_, status_, ingress_count_, dispatch_count_, status_ == TReferencePrecalculationStatus::supply_interrupted};
    }
    [[nodiscard]] constexpr TIngressReferenceSupplyView ingress_supply_view() const noexcept { return TIngressReferenceSupplyView{supply_view()}; }
    [[nodiscard]] constexpr TDispatchReferenceSupplyView dispatch_supply_view() const noexcept { return TDispatchReferenceSupplyView{supply_view()}; }

    template <typename Registry, std::size_t CandidateCount>
    constexpr TReferencePrecalculationReport replenish_ingress(const Registry& registry, const std::array<TReferenceCandidate, CandidateCount>& candidates, TRoundId round_id, TReferenceReportId report_id) noexcept {
        std::uint32_t prepared = 0U;
        status_ = TReferencePrecalculationStatus::replenishing;
        for (const auto& candidate : candidates) {
            if (ingress_count_ >= IngressPoolCapacity || ingress_count_ >= policy_.ingress_supply_depth) break;
            auto reject = validate_ingress_candidate(registry, candidate, round_id);
            if (reject.rejected()) {
                last_rejection_ = reject;
                continue;
            }
            const auto* container = registry.try_get(candidate.container_index);
            const auto slot_index = container->find_first_ingress_writable_slot();
            ingress_pool_[ingress_count_++] = make_ingress_ref(candidate.container_index, slot_index, round_id, registry.generation());
            ++prepared;
        }
        status_ = ingress_count_ > 0U ? TReferencePrecalculationStatus::ingress_refs_ready : TReferencePrecalculationStatus::waiting_for_candidates;
        return TReferencePrecalculationReport{report_id, id_, status_, prepared, 0U};
    }

    template <typename Registry, std::size_t CandidateCount>
    constexpr TReferencePrecalculationReport replenish_dispatch(const Registry& registry, const std::array<TReferenceCandidate, CandidateCount>& candidates, TRoundId round_id, TReferenceReportId report_id) noexcept {
        std::uint32_t prepared = 0U;
        status_ = TReferencePrecalculationStatus::replenishing;
        for (const auto& candidate : candidates) {
            if (dispatch_count_ >= DispatchPoolCapacity || dispatch_count_ >= policy_.dispatch_supply_depth) break;
            auto reject = validate_dispatch_candidate(registry, candidate, round_id);
            if (reject.rejected()) {
                last_rejection_ = reject;
                continue;
            }
            const auto* container = registry.try_get(candidate.container_index);
            const auto slot_index = container->find_first_dispatch_ready_slot();
            dispatch_pool_[dispatch_count_++] = make_dispatch_ref(candidate.container_index, slot_index, round_id, registry.generation());
            ++prepared;
        }
        status_ = dispatch_count_ > 0U ? TReferencePrecalculationStatus::dispatch_refs_ready : TReferencePrecalculationStatus::waiting_for_candidates;
        return TReferencePrecalculationReport{report_id, id_, status_, 0U, prepared};
    }

    [[nodiscard]] constexpr TIngressAccessRef peek_next_ingress() const noexcept {
        return ingress_count_ > 0U ? ingress_pool_[0] : TIngressAccessRef{};
    }

    [[nodiscard]] constexpr TDispatchAccessRef peek_next_dispatch() const noexcept {
        return dispatch_count_ > 0U ? dispatch_pool_[0] : TDispatchAccessRef{};
    }

    constexpr TIngressAccessRef pop_next_ingress() noexcept {
        if (ingress_count_ == 0U) {
            status_ = TReferencePrecalculationStatus::supply_interrupted;
            return TIngressAccessRef{};
        }
        auto result = ingress_pool_[0];
        for (std::uint32_t i = 1; i < ingress_count_; ++i) ingress_pool_[i-1] = ingress_pool_[i];
        --ingress_count_;
        return result;
    }

    constexpr TDispatchAccessRef pop_next_dispatch() noexcept {
        if (dispatch_count_ == 0U) {
            status_ = TReferencePrecalculationStatus::supply_interrupted;
            return TDispatchAccessRef{};
        }
        auto result = dispatch_pool_[0];
        for (std::uint32_t i = 1; i < dispatch_count_; ++i) dispatch_pool_[i-1] = dispatch_pool_[i];
        --dispatch_count_;
        return result;
    }

    [[nodiscard]] constexpr TReferenceCandidateRejectionReport last_rejection() const noexcept { return last_rejection_; }

    [[nodiscard]] constexpr TReferenceSupplyInterruptionReport interruption_report(TReferenceReportId id) const noexcept {
        return TReferenceSupplyInterruptionReport{id, id_, status_, policy_.continuous_supply_required};
    }

private:
    template <typename Registry>
    constexpr TReferenceCandidateRejectionReport validate_ingress_candidate(const Registry& registry, TReferenceCandidate candidate, TRoundId round_id) const noexcept {
        if (!candidate.is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::invalid_registry_index);
        if (!round_id.is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::round_scope_invalid);
        const auto* container = registry.try_get(candidate.container_index);
        if (!container) return reject(candidate, TReferenceCandidateRejectionKind::container_missing);
        if (!ingress_reference_candidate(container->state())) return reject(candidate, TReferenceCandidateRejectionKind::container_state_mismatch);
        if (!container->find_first_ingress_writable_slot().is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::slot_not_found);
        return reject(candidate, TReferenceCandidateRejectionKind::none);
    }

    template <typename Registry>
    constexpr TReferenceCandidateRejectionReport validate_dispatch_candidate(const Registry& registry, TReferenceCandidate candidate, TRoundId round_id) const noexcept {
        if (!candidate.is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::invalid_registry_index);
        if (!round_id.is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::round_scope_invalid);
        const auto* container = registry.try_get(candidate.container_index);
        if (!container) return reject(candidate, TReferenceCandidateRejectionKind::container_missing);
        if (!dispatch_reference_candidate(container->state())) return reject(candidate, TReferenceCandidateRejectionKind::container_state_mismatch);
        if (!container->find_first_dispatch_ready_slot().is_valid()) return reject(candidate, TReferenceCandidateRejectionKind::slot_not_found);
        return reject(candidate, TReferenceCandidateRejectionKind::none);
    }

    [[nodiscard]] constexpr TReferenceCandidateRejectionReport reject(TReferenceCandidate candidate, TReferenceCandidateRejectionKind kind) const noexcept {
        return TReferenceCandidateRejectionReport{TReferenceReportId::from_raw(1), id_, candidate.container_index, kind};
    }

    constexpr TIngressAccessRef make_ingress_ref(TContainerRegistryIndex container_index, TSlotIndex slot_index, TRoundId round_id, std::uint64_t registry_generation) noexcept {
        return TIngressAccessRef{TSlotAccessRef{next_id(), TAccessRefKind::ingress_access, TAccessRefDirection::ingress, TAccessRefScope{container_index, slot_index, round_id, registry_generation, profile_generation_}, TReferenceValidityState::issued}};
    }

    constexpr TDispatchAccessRef make_dispatch_ref(TContainerRegistryIndex container_index, TSlotIndex slot_index, TRoundId round_id, std::uint64_t registry_generation) noexcept {
        return TDispatchAccessRef{TSlotAccessRef{next_id(), TAccessRefKind::dispatch_access, TAccessRefDirection::dispatch, TAccessRefScope{container_index, slot_index, round_id, registry_generation, profile_generation_}, TReferenceValidityState::issued}};
    }

    constexpr TAccessRefId next_id() noexcept {
        return TAccessRefId::from_raw(++next_ref_id_);
    }

    TReferencePrecalculatorId id_{};
    TReferenceSupplyPolicy policy_{};
    TReferencePrecalculationStatus status_{TReferencePrecalculationStatus::uninitialized};
    std::uint64_t profile_generation_{1};
    std::uint64_t next_ref_id_{0};
    std::array<TIngressAccessRef, IngressPoolCapacity> ingress_pool_{};
    std::array<TDispatchAccessRef, DispatchPoolCapacity> dispatch_pool_{};
    std::uint32_t ingress_count_{0};
    std::uint32_t dispatch_count_{0};
    TReferenceCandidateRejectionReport last_rejection_{};
};
} // namespace circulation_mechanism
} // namespace assembler

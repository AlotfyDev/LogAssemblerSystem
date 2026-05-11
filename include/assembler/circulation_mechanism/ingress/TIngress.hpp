#pragma once
#include "TIngressId.hpp"
#include "TIngressState.hpp"
#include "TIngressPayloadEnvelopeRef.hpp"
#include "TIngressPlacementStatus.hpp"
#include "boundary/TIngressBoundaryDescriptor.hpp"
#include "policies/TIngressAccessPolicy.hpp"
#include "views/TIngressView.hpp"
#include "views/TIngressAdmissionView.hpp"
#include "views/TIngressPlacementView.hpp"
#include "reports/TIngressPlacementReport.hpp"
#include "reports/TIngressBoundaryReport.hpp"

/*
    TIngress.hpp

    Delivery:
        CME-INGRESS-PROD-W01 — Production Placement Execution Contract

    Current responsibility:
        Executes ingress placement through a valid TIngressAccessRef into a
        target object supplied by the caller.

    Expected target interface:
        target.place_from_ingress_ref(TIngressAccessRef, TIngressPayloadEnvelopeRef) -> bool

    Production capabilities:
        - boundary validation,
        - reference direction/validity validation,
        - payload reference validation,
        - no locating,
        - target placement call,
        - placement reports/views.

    Explicit non-ownership:
        - Does not calculate refs.
        - Does not inspect payload content.
        - Does not own target storage.
        - Does not dispatch outward.
*/
namespace assembler {
namespace circulation_mechanism {

class TIngress final {
public:
    constexpr TIngress() noexcept = default;
    constexpr TIngress(TIngressId id, TIngressBoundaryDescriptor boundary) noexcept : id_(id), boundary_(boundary) {
        state_ = id_.is_valid() ? TIngressState::ready : TIngressState::blocked_by_invariant;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id_.is_valid() && boundary_.is_valid(); }
    [[nodiscard]] constexpr TIngressView view() const noexcept { return TIngressView{id_, state_}; }
    [[nodiscard]] constexpr TIngressAdmissionView admission_view() const noexcept { return TIngressAdmissionView{view(), boundary_}; }

    template <typename TPlacementTarget>
    constexpr TIngressPlacementReport place(TIngressReportId report_id, TIngressPayloadEnvelopeRef payload, TIngressAccessRef ref, TPlacementTarget& target) noexcept {
        auto status = TIngressAccessPolicy::validate(payload, ref, boundary_);
        if (status != TIngressPlacementStatus::accepted) {
            state_ = TIngressState::blocked_by_invariant;
            return TIngressPlacementReport{report_id, payload, ref, status};
        }
        state_ = TIngressState::placing;
        const bool placed = target.place_from_ingress_ref(ref, payload);
        state_ = placed ? TIngressState::placed : TIngressState::blocked_by_invariant;
        return TIngressPlacementReport{report_id, payload, ref, placed ? TIngressPlacementStatus::accepted : TIngressPlacementStatus::rejected_target_failed};
    }

    [[nodiscard]] constexpr TIngressBoundaryReport boundary_report(TIngressReportId report_id) const noexcept {
        return TIngressBoundaryReport{report_id, boundary_};
    }

private:
    TIngressId id_{TIngressId::invalid()};
    TIngressBoundaryDescriptor boundary_{};
    TIngressState state_{TIngressState::uninitialized};
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "TDispatcherId.hpp"
#include "TDispatcherStatus.hpp"
#include "TDispatchExposureStatus.hpp"
#include "TDispatchExecutionStatus.hpp"
#include "boundary/TDispatchBoundaryDescriptor.hpp"
#include "profiles/TPassivePullDispatchProfile.hpp"
#include "profiles/TPushDispatchProfile.hpp"
#include "views/TDispatchReadyView.hpp"
#include "views/TDispatchExposureView.hpp"
#include "views/TDispatchBoundaryView.hpp"
#include "reports/TDispatchExposureReport.hpp"
#include "reports/TPassiveExposureReport.hpp"
#include "reports/TBoundaryAssumptionBrokenReport.hpp"
#include "reports/TPushDispatchAttemptReport.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TDispatchAccessRef.hpp"

/*
    TDispatcher.hpp

    Delivery:
        CME-DISPATCHER-PROD-W01 — Production Exposure Execution Contract

    Expected target interface:
        target.expose_from_dispatch_ref(TDispatchAccessRef) -> bool

    Production capabilities:
        - validates boundary,
        - validates dispatch ref shape,
        - passive exposure execution through target,
        - exposure view/report,
        - boundary assumption reports,
        - optional push attempt report without push implementation.

    Non-ownership:
        - Does not calculate refs.
        - Does not copy/move payload.
        - Does not execute bridge protocol.
        - Does not own receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {

class TDispatcher final {
public:
    constexpr TDispatcher() noexcept = default;
    constexpr TDispatcher(TDispatcherId id, TPassivePullDispatchProfile passive, TPushDispatchProfile push, TDispatchBoundaryDescriptor boundary) noexcept
        : id_(id), passive_(passive), push_(push), boundary_(boundary) {
        status_ = is_valid() ? TDispatcherStatus::ready : TDispatcherStatus::boundary_assumption_broken;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && passive_.is_valid() && push_.is_valid() && boundary_.is_valid();
    }

    [[nodiscard]] constexpr TDispatchReadyView ready_view() const noexcept { return TDispatchReadyView{id_, status_}; }
    [[nodiscard]] constexpr TDispatchBoundaryView boundary_view() const noexcept { return TDispatchBoundaryView{boundary_}; }

    template <typename TExposureTarget>
    constexpr TDispatchExposureReport expose_passive(TDispatchReportId report_id, TDispatchAccessRef ref, TExposureTarget& target) noexcept {
        if (!is_valid()) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_invalid_dispatcher};
        if (status_ == TDispatcherStatus::closed) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_closed};
        if (!boundary_.ready() || !boundary_.boundary_safe()) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_boundary_mismatch};
        if (!ref.base.id.is_valid() || !ref.base.scope.is_valid()) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_invalid_ref};
        if (ref.base.kind != TAccessRefKind::dispatch_access || ref.base.direction != TAccessRefDirection::dispatch) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_wrong_ref_direction};
        if (!ref.can_be_consumed_by_dispatcher()) return {report_id, id_, ref, TDispatchExposureStatus::failed, TDispatchExecutionStatus::rejected_invalid_ref};

        status_ = TDispatcherStatus::exposing;
        const bool exposed = target.expose_from_dispatch_ref(ref);
        status_ = exposed ? TDispatcherStatus::passive_exposed : TDispatcherStatus::boundary_assumption_broken;
        return {report_id, id_, ref, exposed ? TDispatchExposureStatus::exposed : TDispatchExposureStatus::failed, exposed ? TDispatchExecutionStatus::accepted : TDispatchExecutionStatus::rejected_target_failed};
    }

    [[nodiscard]] constexpr TPassiveExposureReport passive_exposure_report(TDispatchReportId report_id, TDispatchAccessRef ref) const noexcept {
        return TPassiveExposureReport{TDispatchExposureReport{report_id, id_, ref, TDispatchExposureStatus::exposed, TDispatchExecutionStatus::accepted}, passive_.bridge_observation_required_for_release};
    }

    [[nodiscard]] constexpr TBoundaryAssumptionBrokenReport boundary_assumption_report(TDispatchReportId report_id, bool broken) const noexcept {
        return TBoundaryAssumptionBrokenReport{report_id, id_, broken};
    }

    [[nodiscard]] constexpr TPushDispatchAttemptReport push_attempt_report(TDispatchReportId report_id, bool attempted) const noexcept {
        return TPushDispatchAttemptReport{report_id, id_, attempted, attempted && push_.is_enabled()};
    }

private:
    TDispatcherId id_{TDispatcherId::invalid()};
    TDispatcherStatus status_{TDispatcherStatus::uninitialized};
    TPassivePullDispatchProfile passive_{};
    TPushDispatchProfile push_{};
    TDispatchBoundaryDescriptor boundary_{};
};
} // namespace circulation_mechanism
} // namespace assembler

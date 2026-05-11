#pragma once
#include "TReadSideCapacityReportId.hpp"
#include "TReadSideCapacityIssueKind.hpp"
#include "../backpressure/TReadSideBackpressureState.hpp"
#include "../delayed_release/TDelayedReleaseState.hpp"
#include "../backpressure/TBackpressureDecisionKind.hpp"
#include "../delayed_release/TDelayedReleaseDecisionKind.hpp"

/*
    TReadSideCapacityReport.hpp

    Responsibility:
        Evidence for read-side capacity/backpressure/delayed-release decisions.

    Non-ownership:
        Does not execute recovery or call receiver.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideCapacityReport final {
    TReadSideCapacityReportId report_id{};
    TReadSideCapacityIssueKind issue{TReadSideCapacityIssueKind::none};
    TReadSideBackpressureState backpressure_state{TReadSideBackpressureState::none};
    TDelayedReleaseState delayed_release_state{TDelayedReleaseState::not_delayed};
    TBackpressureDecisionKind backpressure_decision{TBackpressureDecisionKind::allow_admission};
    TDelayedReleaseDecisionKind delayed_release_decision{TDelayedReleaseDecisionKind::not_applicable};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
    [[nodiscard]] constexpr bool has_issue() const noexcept { return issue != TReadSideCapacityIssueKind::none; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

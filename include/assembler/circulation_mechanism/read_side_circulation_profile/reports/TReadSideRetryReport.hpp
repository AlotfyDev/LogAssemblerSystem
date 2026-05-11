#pragma once
#include "TReadSideRetryReportId.hpp"
#include "TReadSideRetryIssueKind.hpp"
#include "../retry/TRetryAttempt.hpp"
#include "../retry/TRetryDecisionKind.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideRetryReport final {
    TReadSideRetryReportId report_id{};
    TRetryAttempt attempt{};
    TRetryDecisionKind decision{TRetryDecisionKind::not_applicable};
    TReadSideRetryIssueKind issue{TReadSideRetryIssueKind::none};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
    [[nodiscard]] constexpr bool has_issue() const noexcept { return issue != TReadSideRetryIssueKind::none; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

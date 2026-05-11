#pragma once
#include "TCapacityProfileId.hpp"
#include "TCapacityIssueKind.hpp"
#include "TCapacityProfileStatus.hpp"

/*
    TCapacityProfileReport.hpp

    Responsibility:
        Records evidence for capacity profile validation or change.

    Explicit non-ownership:
        Report does not execute scaling or recovery.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCapacityProfileReport final
{
    TCapacityProfileId profile_id{};
    TCapacityIssueKind issue_kind{TCapacityIssueKind::none};
    TCapacityProfileStatus observed_status{TCapacityProfileStatus::undefined};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile_id.is_valid(); }
    [[nodiscard]] constexpr bool has_issue() const noexcept { return issue_kind != TCapacityIssueKind::none; }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && !has_issue() && observed_status != TCapacityProfileStatus::invalid; }
};
} // namespace circulation_mechanism
} // namespace assembler

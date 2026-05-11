#pragma once
#include "TReadSideProfileReportId.hpp"
#include "TReadSideProfileIssueKind.hpp"
#include "../TReadSideProfileId.hpp"
#include "../TReadSideProfileStatus.hpp"
#include "../TReadSideProfileValidationResult.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideProfileReadinessReport final {
    TReadSideProfileReportId report_id{};
    TReadSideProfileId profile_id{};
    TReadSideProfileStatus status{TReadSideProfileStatus::undefined};
    TReadSideProfileIssueKind issue{TReadSideProfileIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && profile_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid()
            && issue == TReadSideProfileIssueKind::none
            && (status == TReadSideProfileStatus::ready || status == TReadSideProfileStatus::active);
    }
    [[nodiscard]] static constexpr TReadSideProfileReadinessReport from_validation(
        TReadSideProfileReportId report_id,
        TReadSideProfileId profile_id,
        TReadSideProfileStatus status,
        TReadSideProfileValidationResult result) noexcept
    {
        return TReadSideProfileReadinessReport{report_id, profile_id, status, result.issue};
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

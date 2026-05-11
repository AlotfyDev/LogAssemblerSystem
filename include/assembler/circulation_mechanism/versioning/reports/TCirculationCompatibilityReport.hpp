#pragma once
#include "TCirculationCompatibilityReportId.hpp"
#include "../TCirculationCompatibilityStatus.hpp"
#include "../TCirculationVersionIssueKind.hpp"
#include "../TCirculationVersionSet.hpp"
#include "../features/TCirculationFeatureFlagSet.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationCompatibilityReport final {
    TCirculationCompatibilityReportId report_id{};
    TCirculationVersionSet requested{};
    TCirculationVersionSet supported{};
    TCirculationFeatureFlagSet features{};
    TCirculationCompatibilityStatus status{TCirculationCompatibilityStatus::unknown};
    TCirculationVersionIssueKind issue{TCirculationVersionIssueKind::none};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && requested.is_valid() && supported.is_valid(); }
    [[nodiscard]] constexpr bool compatible() const noexcept {
        return is_valid() && issue == TCirculationVersionIssueKind::none && (status == TCirculationCompatibilityStatus::compatible || status == TCirculationCompatibilityStatus::compatible_with_deprecation);
    }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

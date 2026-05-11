#pragma once

#include "TProductionReadinessCriterionKind.hpp"
#include "TProductionReadinessIssueKind.hpp"
#include "TProductionReadinessSeverity.hpp"

/*
    TProductionReadinessEvidence.hpp

    Responsibility:
        Describes one piece of readiness evidence.

    Non-ownership:
        Does not run the test. Records the result of evidence supplied by tests/reports.
*/

namespace assembler {
namespace circulation_mechanism {

struct TProductionReadinessEvidence final {
    TProductionReadinessCriterionKind criterion{TProductionReadinessCriterionKind::manifest_and_evidence};
    bool present{false};
    bool passed{false};
    TProductionReadinessIssueKind issue{TProductionReadinessIssueKind::none};
    TProductionReadinessSeverity severity{TProductionReadinessSeverity::info};

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return present && passed && issue == TProductionReadinessIssueKind::none;
    }

    [[nodiscard]] constexpr bool blocking() const noexcept {
        return severity == TProductionReadinessSeverity::error || severity == TProductionReadinessSeverity::critical;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

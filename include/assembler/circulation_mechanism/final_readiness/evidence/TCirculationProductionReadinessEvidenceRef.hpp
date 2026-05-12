#pragma once
#include "../criteria/TCirculationProductionReadinessCriterionKind.hpp"
#include "../TCirculationProductionReadinessIssueKind.hpp"
#include "../TCirculationProductionReadinessSeverity.hpp"

/*
    TCirculationProductionReadinessEvidenceRef.hpp

    Current responsibility:
        Describes one evidence item used by the final production readiness gate.

    Non-ownership:
        Evidence ref does not run tests or store external reports.
*/
namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

struct TCirculationProductionReadinessEvidenceRef final {
    TCirculationProductionReadinessCriterionKind criterion{TCirculationProductionReadinessCriterionKind::manifest_evidence_complete};
    bool present{false};
    bool passed{false};
    TCirculationProductionReadinessIssueKind issue{TCirculationProductionReadinessIssueKind::none};
    TCirculationProductionReadinessSeverity severity{TCirculationProductionReadinessSeverity::info};

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return present && passed && issue == TCirculationProductionReadinessIssueKind::none;
    }

    [[nodiscard]] constexpr bool blocking() const noexcept {
        return severity == TCirculationProductionReadinessSeverity::error
            || severity == TCirculationProductionReadinessSeverity::critical;
    }
};
} // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

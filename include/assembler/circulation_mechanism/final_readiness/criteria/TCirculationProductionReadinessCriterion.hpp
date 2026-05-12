#pragma once
#include "../evidence/TCirculationProductionReadinessEvidenceRef.hpp"

/*
    TCirculationProductionReadinessCriterion.hpp

    Current responsibility:
        Required/optional final readiness criterion with evidence reference.

    Non-ownership:
        Does not execute the underlying evidence producer.
*/
namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

struct TCirculationProductionReadinessCriterion final {
    TCirculationProductionReadinessCriterionKind kind{TCirculationProductionReadinessCriterionKind::manifest_evidence_complete};
    bool required{true};
    TCirculationProductionReadinessEvidenceRef evidence{};

    [[nodiscard]] constexpr bool satisfied() const noexcept {
        return !required || evidence.accepted();
    }

    [[nodiscard]] constexpr bool blocking_failure() const noexcept {
        return required && !evidence.accepted() && evidence.blocking();
    }
};
} // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

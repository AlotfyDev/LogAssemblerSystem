#pragma once

#include "TProductionReadinessEvidence.hpp"

/*
    TProductionReadinessCriterion.hpp

    Responsibility:
        Defines a required production readiness criterion with evidence.

    Non-ownership:
        Does not execute tests or mutate runtime.
*/

namespace assembler {
namespace circulation_mechanism {

struct TProductionReadinessCriterion final {
    TProductionReadinessCriterionKind kind{TProductionReadinessCriterionKind::manifest_and_evidence};
    bool required{true};
    TProductionReadinessEvidence evidence{};

    [[nodiscard]] constexpr bool satisfied() const noexcept {
        return !required || evidence.accepted();
    }

    [[nodiscard]] constexpr bool blocking_failure() const noexcept {
        return required && !evidence.accepted() && evidence.blocking();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

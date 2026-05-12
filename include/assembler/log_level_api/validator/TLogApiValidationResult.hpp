#pragma once

/*
    LOGAPI-W03 — Validator Contract And Binding Surface

    Responsibility:
        Define validation contracts, validation result carriers, validation issues,
        validator capabilities, safe points, and configuration-time validator
        binding descriptors.

    Boundary:
        No concrete validators, concrete schemas, metadata structs, timestamp
        algorithms, envelope assembly, API hot path, communication bindings,
        or policy assignment.

    Doctrine:
        Validator contracts are core.
        Concrete validators are schema-family add-ons.
        Validator binding is resolved before the hot path.
*/

#include <vector>

#include "TLogApiValidationIssue.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidationResult final {
    bool accepted{false};
    std::vector<TLogApiValidationIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return accepted && !HasBlockingIssue();
    }

    [[nodiscard]] static TLogApiValidationResult Accepted() {
        TLogApiValidationResult r{};
        r.accepted = true;
        return r;
    }
};

} // namespace assembler::log_level_api::validator

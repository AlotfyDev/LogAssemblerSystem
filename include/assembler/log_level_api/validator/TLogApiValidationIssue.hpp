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

#include <string>

#include "TLogApiValidationSeverity.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidationIssue final {
    std::string code{};
    std::string message{};
    TLogApiValidationSeverity severity{TLogApiValidationSeverity::Unknown};
    bool blocking{false};

    [[nodiscard]] bool HasIssue() const noexcept {
        return !code.empty() || !message.empty();
    }
};

} // namespace assembler::log_level_api::validator

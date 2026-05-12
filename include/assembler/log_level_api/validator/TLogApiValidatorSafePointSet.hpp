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

#include "TLogApiValidatorSafePointKind.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidatorSafePointSet final {
    std::vector<TLogApiValidatorSafePointKind> safe_points{};

    [[nodiscard]] bool Supports(TLogApiValidatorSafePointKind safe_point) const noexcept {
        for (const auto& item : safe_points) {
            if (item == safe_point) return true;
        }
        return false;
    }
};

} // namespace assembler::log_level_api::validator

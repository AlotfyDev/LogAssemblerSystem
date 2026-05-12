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

#include "TLogApiValidationMode.hpp"
#include "TLogApiValidatorId.hpp"
#include "TLogApiValidatorStatus.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidatorBindingDescriptor final {
    TLogApiValidatorId validator_id{};
    TLogApiValidatorStatus status{TLogApiValidatorStatus::Unknown};
    TLogApiValidationMode mode{TLogApiValidationMode::Unknown};

    std::string binding_name{};
    std::string concrete_validator_symbol{};
    std::string supported_content_profile_name{};

    [[nodiscard]] bool IsResolved() const noexcept {
        if (!validator_id.IsValid()) return false;
        if (status != TLogApiValidatorStatus::Resolved && status != TLogApiValidatorStatus::Active) return false;
        if (mode == TLogApiValidationMode::Unknown || mode == TLogApiValidationMode::None) return false;
        if (binding_name.empty()) return false;
        if (concrete_validator_symbol.empty()) return false;
        if (supported_content_profile_name.empty()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::validator

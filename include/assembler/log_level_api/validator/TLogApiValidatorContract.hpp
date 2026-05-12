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
#include "TLogApiValidatorCapabilitySet.hpp"
#include "TLogApiValidatorId.hpp"
#include "TLogApiValidatorSafePointSet.hpp"
#include "TLogApiValidatorStatus.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidatorContract final {
    TLogApiValidatorId id{};
    TLogApiValidatorStatus status{TLogApiValidatorStatus::Unknown};
    TLogApiValidationMode mode{TLogApiValidationMode::Unknown};

    std::string contract_name{};
    std::string supported_content_profile_name{};

    TLogApiValidatorCapabilitySet capabilities{};
    TLogApiValidatorSafePointSet safe_points{};

    [[nodiscard]] bool IsReadyForBinding() const noexcept {
        if (!id.IsValid()) return false;
        if (status != TLogApiValidatorStatus::Declared &&
            status != TLogApiValidatorStatus::Bound &&
            status != TLogApiValidatorStatus::Resolved &&
            status != TLogApiValidatorStatus::Active) return false;
        if (mode == TLogApiValidationMode::Unknown || mode == TLogApiValidationMode::None) return false;
        if (contract_name.empty()) return false;
        if (supported_content_profile_name.empty()) return false;
        if (!capabilities.Supports(TLogApiValidatorCapabilityKind::ProduceValidationIssues)) return false;
        if (!safe_points.Supports(TLogApiValidatorSafePointKind::BeforeValidation)) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::validator

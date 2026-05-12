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

#include "TLogApiValidationMode.hpp"
#include "TLogApiValidatorBindingDescriptor.hpp"
#include "TLogApiValidatorBindingRegistryView.hpp"
#include "TLogApiValidatorCapabilityKind.hpp"
#include "TLogApiValidatorCapabilitySet.hpp"
#include "TLogApiValidatorContract.hpp"
#include "TLogApiValidatorId.hpp"
#include "TLogApiValidatorSafePointKind.hpp"
#include "TLogApiValidatorSafePointSet.hpp"
#include "TLogApiValidatorStatus.hpp"

namespace assembler::log_level_api::validator {

class TLogApiValidatorBindingResolver final {
public:
    [[nodiscard]] static TLogApiValidatorContract MakeDefaultJsonContract() {
        TLogApiValidatorContract c{};
        c.id = TLogApiValidatorId{1};
        c.status = TLogApiValidatorStatus::Declared;
        c.mode = TLogApiValidationMode::Structural;
        c.contract_name = "default.json.validator.contract";
        c.supported_content_profile_name = "default.json.minimal";
        c.capabilities.capabilities = {
            TLogApiValidatorCapabilityKind::ValidateContentPresence,
            TLogApiValidatorCapabilityKind::ValidateContentShape,
            TLogApiValidatorCapabilityKind::ValidateRequiredFields,
            TLogApiValidatorCapabilityKind::ProduceValidationIssues
        };
        c.safe_points.safe_points = {
            TLogApiValidatorSafePointKind::BeforeValidation,
            TLogApiValidatorSafePointKind::AfterValidation,
            TLogApiValidatorSafePointKind::OnValidationFailure
        };
        return c;
    }

    [[nodiscard]] static TLogApiValidatorBindingDescriptor MakeDefaultJsonBinding() {
        TLogApiValidatorBindingDescriptor b{};
        b.validator_id = TLogApiValidatorId{1};
        b.status = TLogApiValidatorStatus::Resolved;
        b.mode = TLogApiValidationMode::Structural;
        b.binding_name = "default.json.validator.binding";
        b.concrete_validator_symbol = "DefaultJsonContentValidator";
        b.supported_content_profile_name = "default.json.minimal";
        return b;
    }

    [[nodiscard]] static TLogApiValidatorBindingRegistryView MakeDefaultRegistryView() {
        TLogApiValidatorBindingRegistryView v{};
        v.bindings.push_back(MakeDefaultJsonBinding());
        return v;
    }
};

} // namespace assembler::log_level_api::validator

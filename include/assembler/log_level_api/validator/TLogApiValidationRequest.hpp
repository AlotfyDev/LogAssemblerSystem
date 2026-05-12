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

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileDescriptor.hpp"

#include "TLogApiValidatorBindingDescriptor.hpp"

namespace assembler::log_level_api::validator {

struct TLogApiValidationRequest final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};
    const assembler::log_level_api::content::TLogApiContentProfileDescriptor* content_profile{nullptr};
    const TLogApiValidatorBindingDescriptor* validator_binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        if (!content.IsPresent()) return false;
        if (content_profile == nullptr || !content_profile->IsReadyForConfigurationUse()) return false;
        if (content_profile->validation_required) {
            return validator_binding != nullptr && validator_binding->IsResolved();
        }
        return true;
    }
};

} // namespace assembler::log_level_api::validator

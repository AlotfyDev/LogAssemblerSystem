#pragma once

/*
    LOGAPI-W06 — API Facade Content-Only Input

    This header belongs to the Log Level API consuming facade layer.

    Responsibility:
        Define the content-only API input surface and admission result carriers
        that consume a previously resolved active profile.

    Boundary:
        The API facade receives content only.
        It must not receive schema definitions, metadata struct definitions,
        validator bindings, timestamp stabilization rules, envelope assembly
        instructions, communication bindings, or policy assignment material with
        every payload.

    Doctrine:
        Configure first. Consume content only.
        The API facade uses an already resolved active profile.
*/

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/api_configurator/TLogApiActiveProfile.hpp"

namespace assembler::log_level_api::api_facade {

/*
    Accepted content carrier after facade admission.

    Still content-focused: this does not contain schema definitions, metadata
    structs, timestamp values, or envelope material.
*/
struct TLogApiFacadeAcceptedContent final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};
    const assembler::log_level_api::api_configurator::TLogApiActiveProfile* active_profile{nullptr};

    [[nodiscard]] bool IsValid() const noexcept {
        return content.IsPresent()
            && active_profile != nullptr
            && active_profile->IsReadyForConsumingPath();
    }
};

} // namespace assembler::log_level_api::api_facade

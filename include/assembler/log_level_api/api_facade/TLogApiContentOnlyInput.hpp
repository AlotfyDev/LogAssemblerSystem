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

namespace assembler::log_level_api::api_facade {

/*
    Hot-path API input.

    This object carries content only.
    It intentionally carries no schema metadata, metadata struct, validator binding,
    timestamp stabilizer config, envelope assembler selection, or policy data.
*/
struct TLogApiContentOnlyInput final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return content.IsPresent();
    }
};

} // namespace assembler::log_level_api::api_facade

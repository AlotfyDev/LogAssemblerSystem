#pragma once

/*
    LOGAPI-W27 — Public API Surface And Usage Model

    Responsibility:
        Define stable public API call surfaces for content-only usage:
        opaque payload input, JSON input, C-style struct primitive input,
        typed payload references, public result/error models, and usage-facing
        facade entry points.

    Boundary:
        Public API calls must not accept schema definitions, metadata structures,
        validator bindings, timestamp stabilization rules, assembler selection,
        circulation settings, or policy material per call.

    Doctrine:
        Configure first. Consume content only.
        Public API call surfaces are stable front doors over already resolved
        profiles and previously prepared binding/handoff contracts.
*/

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"

namespace assembler::log_level_api::public_api {

struct TLogApiOpaquePayloadRef final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return content.IsPresent();
    }
};

} // namespace assembler::log_level_api::public_api

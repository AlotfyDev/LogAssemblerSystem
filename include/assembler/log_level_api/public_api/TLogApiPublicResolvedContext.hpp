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

#include "assembler/log_level_api/api_configurator/TLogApiActiveProfile.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationTargetDescriptor.hpp"

namespace assembler::log_level_api::public_api {

/*
    Resolved public API context.

    This is prepared before calls. It proves that the public API has resolved
    configuration, parser binding, and circulation target references.
*/
struct TLogApiPublicResolvedContext final {
    const assembler::log_level_api::api_configurator::TLogApiActiveProfile* active_profile{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* parser_binding{nullptr};
    assembler::log_level_api::communication_bindings::circulation_handoff::TLogApiCirculationTargetDescriptor circulation_target{};

    [[nodiscard]] bool IsReady() const noexcept {
        return active_profile != nullptr
            && active_profile->IsReadyForConsumingPath()
            && parser_binding != nullptr
            && parser_binding->IsResolved()
            && circulation_target.IsResolved();
    }
};

} // namespace assembler::log_level_api::public_api

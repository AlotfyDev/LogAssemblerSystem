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

#include <string>
#include <vector>

namespace assembler::log_level_api::public_api {

struct TLogApiPublicApiUsageModel final {
    std::vector<std::string> supported_input_paths{
        "opaque_payload",
        "json_text",
        "c_style_struct_primitive_buffer"
    };

    std::vector<std::string> forbidden_per_call_material{
        "schema_definition",
        "metadata_struct_definition",
        "validator_binding",
        "timestamp_stabilizer_config",
        "assembler_family_selection",
        "circulation_settings",
        "policy_material"
    };
};

} // namespace assembler::log_level_api::public_api

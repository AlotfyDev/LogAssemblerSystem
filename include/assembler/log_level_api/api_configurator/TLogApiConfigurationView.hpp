#pragma once

/*
    LOGAPI-W01 — Configuration Surface And Default Profile

    This header belongs to the Log Level API configuration surface.

    Responsibility:
        Provide configuration-time types that allow Log Level API to be prepared
        before the consuming hot path receives content.

    Boundary:
        This file must not define concrete content schemas, concrete validators,
        metadata field implementation, timestamp stabilization algorithms,
        envelope assembly behavior, circulation handoff, or policy assignment.

    Doctrine:
        Configure first. Consume content only.
        The hot path uses an already resolved active profile.
*/

#include <string>

#include "TLogApiActiveProfile.hpp"

namespace assembler::log_level_api::api_configurator {

struct TLogApiConfigurationView final {
    std::string profile_name{};
    std::string schema_path{};
    std::string assembler_family{};
    bool validation_required{false};
    bool metadata_enabled{false};
    bool timestamp_stabilization_enabled{false};
    bool ready_for_consuming_path{false};

    [[nodiscard]] static TLogApiConfigurationView From(const TLogApiActiveProfile& profile) {
        TLogApiConfigurationView view{};
        view.profile_name = profile.content_profile_name;
        view.validation_required = profile.validation_required;
        view.metadata_enabled = profile.metadata_enabled;
        view.timestamp_stabilization_enabled = profile.timestamp_stabilization_enabled;
        view.ready_for_consuming_path = profile.IsReadyForConsumingPath();

        switch (profile.schema_path) {
            case TLogApiSchemaPathKind::Json: view.schema_path = "json"; break;
            case TLogApiSchemaPathKind::CStyleStructPrimitives: view.schema_path = "c_style_struct_primitives"; break;
            default: view.schema_path = "unknown"; break;
        }

        switch (profile.assembler_family) {
            case TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler: view.assembler_family = "plain_envelope_assembler"; break;
            case TLogApiAssemblerFamilyKind::ValidatorComposedEnvelopeAssembler: view.assembler_family = "validator_composed_envelope_assembler"; break;
            default: view.assembler_family = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::api_configurator

#pragma once

/*
    LOGAPI-W20 — Metadata Default Field Packs

    Responsibility:
        Define default metadata field packs and helpers for composing reusable
        metadata field/value groups into metadata profile configurations.

    Boundary:
        Metadata field packs are configuration conveniences, not policy objects.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff,
        persistence, or policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Default field packs reduce repeated per-call payload authoring.
        Metadata values remain mutable through profile/update surfaces.
*/

#include <string>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataStructDescriptor.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataStructId.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataStructStatus.hpp"

#include "TLogApiMetadataDefaultFieldPackSet.hpp"
#include "TLogApiMetadataFieldPackCompositionResult.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

class TLogApiMetadataFieldPackComposer final {
public:
    [[nodiscard]] static TLogApiMetadataFieldPackCompositionResult Compose(
        const TLogApiMetadataDefaultFieldPackSet& set,
        const char* struct_name = "default.composed.metadata.struct"
    ) {
        TLogApiMetadataFieldPackCompositionResult result{};

        if (!set.IsDeclared()) {
            result.issues.push_back({
                "LOGAPI_METADATA_FIELD_PACK_SET_INVALID",
                "Default metadata field pack set is not declared.",
                true
            });
            return result;
        }

        result.config.metadata_struct.id = assembler::log_level_api::metadata_injector::TLogApiMetadataStructId{100};
        result.config.metadata_struct.status = assembler::log_level_api::metadata_injector::TLogApiMetadataStructStatus::Resolved;
        result.config.metadata_struct.struct_name = struct_name;
        result.config.metadata_struct.schema_id = "default.composed.metadata.schema";
        result.config.metadata_struct.schema_family = "logapi.default.composed";
        result.config.metadata_struct.schema_version = "v1";
        result.config.metadata_struct.schema_kind = "metadata";

        for (const auto& pack : set.packs) {
            for (const auto& field : pack.fields) {
                result.config.metadata_struct.fields.push_back(field);
            }
            for (const auto& value : pack.values.values) {
                result.config.default_values.values.push_back(value);
            }
        }

        if (!result.config.IsReady()) {
            result.issues.push_back({
                "LOGAPI_METADATA_COMPOSED_CONFIG_NOT_READY",
                "Composed metadata config is not ready.",
                true
            });
        }

        return result;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs

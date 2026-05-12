#pragma once

/*
    LOGAPI-W04 — Metadata Struct And Field Values

    This header belongs to the Log Level API metadata struct and field value layer.

    Responsibility:
        Define metadata struct descriptors, metadata fields, mutable metadata
        values, update sets, prepared metadata blocks, and metadata injector
        configuration surfaces.

    Boundary:
        Metadata is not content.
        Metadata is not stabilized timestamp.
        Metadata does not define content schema fields, required/default validator
        inputs, concrete validators, timestamp stabilization algorithms, envelope
        assembly, communication bindings, or policy assignment.

    Doctrine:
        Content + metadata struct + stabilized timestamp meet later inside the
        envelope through the envelope assembler.
*/

#include <string>

#include "TLogApiMetadataInjectorConfig.hpp"

namespace assembler::log_level_api::metadata_injector {

struct TLogApiDefaultMetadataProfile final {
    [[nodiscard]] static TLogApiMetadataInjectorConfig Make() {
        TLogApiMetadataFieldDescriptor schema_id_field{};
        schema_id_field.id = TLogApiMetadataFieldId{1};
        schema_id_field.field_name = "schema_id";
        schema_id_field.value_kind = TLogApiMetadataFieldValueKind::String;

        TLogApiMetadataFieldDescriptor schema_family_field{};
        schema_family_field.id = TLogApiMetadataFieldId{2};
        schema_family_field.field_name = "schema_family";
        schema_family_field.value_kind = TLogApiMetadataFieldValueKind::String;

        TLogApiMetadataFieldDescriptor schema_version_field{};
        schema_version_field.id = TLogApiMetadataFieldId{3};
        schema_version_field.field_name = "schema_version";
        schema_version_field.value_kind = TLogApiMetadataFieldValueKind::String;

        TLogApiMetadataFieldDescriptor schema_kind_field{};
        schema_kind_field.id = TLogApiMetadataFieldId{4};
        schema_kind_field.field_name = "schema_kind";
        schema_kind_field.value_kind = TLogApiMetadataFieldValueKind::String;

        TLogApiMetadataStructDescriptor descriptor{};
        descriptor.id = TLogApiMetadataStructId{1};
        descriptor.status = TLogApiMetadataStructStatus::Resolved;
        descriptor.struct_name = "default.logapi.metadata.struct";
        descriptor.schema_id = "default.logapi.schema";
        descriptor.schema_family = "logapi.default";
        descriptor.schema_version = "v1";
        descriptor.schema_kind = "metadata";
        descriptor.fields = {
            schema_id_field,
            schema_family_field,
            schema_version_field,
            schema_kind_field
        };

        TLogApiMetadataValueSet values{};
        values.values.push_back({schema_id_field.id, TLogApiMetadataFieldValueKind::String, std::string{"default.logapi.schema"}});
        values.values.push_back({schema_family_field.id, TLogApiMetadataFieldValueKind::String, std::string{"logapi.default"}});
        values.values.push_back({schema_version_field.id, TLogApiMetadataFieldValueKind::String, std::string{"v1"}});
        values.values.push_back({schema_kind_field.id, TLogApiMetadataFieldValueKind::String, std::string{"metadata"}});

        TLogApiMetadataInjectorConfig config{};
        config.metadata_struct = descriptor;
        config.default_values = values;
        return config;
    }
};

} // namespace assembler::log_level_api::metadata_injector

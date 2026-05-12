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
#include <vector>

#include "TLogApiMetadataStructDescriptor.hpp"

namespace assembler::log_level_api::metadata_injector {

struct TLogApiMetadataStructView final {
    std::string struct_name{};
    std::string schema_id{};
    std::string schema_family{};
    std::string schema_version{};
    std::string schema_kind{};
    std::vector<std::string> field_names{};
    bool resolved{false};

    [[nodiscard]] static TLogApiMetadataStructView From(const TLogApiMetadataStructDescriptor& d) {
        TLogApiMetadataStructView v{};
        v.struct_name = d.struct_name;
        v.schema_id = d.schema_id;
        v.schema_family = d.schema_family;
        v.schema_version = d.schema_version;
        v.schema_kind = d.schema_kind;
        v.resolved = d.IsResolved();
        for (const auto& field : d.fields) {
            v.field_names.push_back(field.field_name);
        }
        return v;
    }
};

} // namespace assembler::log_level_api::metadata_injector

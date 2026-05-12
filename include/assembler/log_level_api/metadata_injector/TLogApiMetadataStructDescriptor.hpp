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

#include "TLogApiMetadataFieldDescriptor.hpp"
#include "TLogApiMetadataStructId.hpp"
#include "TLogApiMetadataStructStatus.hpp"

namespace assembler::log_level_api::metadata_injector {

/*
    Metadata struct descriptor.

    This descriptor owns schema identity/classification metadata such as schema id,
    family, version, and kind. These values are metadata, not content fields and
    not validator inputs.
*/
struct TLogApiMetadataStructDescriptor final {
    TLogApiMetadataStructId id{};
    TLogApiMetadataStructStatus status{TLogApiMetadataStructStatus::Unknown};

    std::string struct_name{};
    std::string schema_id{};
    std::string schema_family{};
    std::string schema_version{};
    std::string schema_kind{};

    std::vector<TLogApiMetadataFieldDescriptor> fields{};

    [[nodiscard]] bool IsResolved() const noexcept {
        if (!id.IsValid()) return false;
        if (status != TLogApiMetadataStructStatus::Resolved
            && status != TLogApiMetadataStructStatus::Active) return false;
        if (struct_name.empty()) return false;
        if (schema_id.empty() || schema_family.empty() || schema_version.empty() || schema_kind.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsDeclared()) return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::metadata_injector

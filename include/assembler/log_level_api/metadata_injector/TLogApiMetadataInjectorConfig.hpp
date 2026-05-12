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

#include "TLogApiMetadataStructDescriptor.hpp"
#include "TLogApiMetadataValueSet.hpp"

namespace assembler::log_level_api::metadata_injector {

struct TLogApiMetadataInjectorConfig final {
    TLogApiMetadataStructDescriptor metadata_struct{};
    TLogApiMetadataValueSet default_values{};

    [[nodiscard]] bool IsReady() const noexcept {
        if (!metadata_struct.IsResolved()) return false;
        for (const auto& field : metadata_struct.fields) {
            if (field.enabled && default_values.Find(field.id) == nullptr) return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::metadata_injector

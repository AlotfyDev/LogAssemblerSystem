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

/*
    Prepared metadata block.

    This block is independent from content and timestamp. It is assembled with
    content and stabilized timestamp later by the envelope assembler.
*/
struct TLogApiPreparedMetadataBlock final {
    TLogApiMetadataStructDescriptor descriptor{};
    TLogApiMetadataValueSet values{};

    [[nodiscard]] bool IsReadyForEnvelope() const noexcept {
        if (!descriptor.IsResolved()) return false;
        for (const auto& field : descriptor.fields) {
            if (field.enabled && values.Find(field.id) == nullptr) return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::metadata_injector

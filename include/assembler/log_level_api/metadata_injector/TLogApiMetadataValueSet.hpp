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

#include <vector>

#include "TLogApiMetadataFieldValue.hpp"

namespace assembler::log_level_api::metadata_injector {

struct TLogApiMetadataValueSet final {
    std::vector<TLogApiMetadataFieldValue> values{};

    [[nodiscard]] const TLogApiMetadataFieldValue* Find(TLogApiMetadataFieldId id) const noexcept {
        for (const auto& value : values) {
            if (value.field_id.value == id.value) return &value;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::metadata_injector

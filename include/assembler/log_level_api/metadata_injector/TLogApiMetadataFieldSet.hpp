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

#include "TLogApiMetadataFieldDescriptor.hpp"

namespace assembler::log_level_api::metadata_injector {

struct TLogApiMetadataFieldSet final {
    std::vector<TLogApiMetadataFieldDescriptor> fields{};

    [[nodiscard]] bool HasField(TLogApiMetadataFieldId id) const noexcept {
        for (const auto& field : fields) {
            if (field.id.value == id.value) return true;
        }
        return false;
    }
};

} // namespace assembler::log_level_api::metadata_injector

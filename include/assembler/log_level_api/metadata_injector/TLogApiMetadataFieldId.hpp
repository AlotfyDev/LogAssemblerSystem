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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::metadata_injector {

struct TLogApiMetadataFieldId final {
    std::uint64_t value{0};

    constexpr TLogApiMetadataFieldId() = default;
    constexpr explicit TLogApiMetadataFieldId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-metadata-field-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::metadata_injector

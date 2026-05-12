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
#include <variant>

#include "TLogApiMetadataFieldId.hpp"
#include "TLogApiMetadataFieldValueKind.hpp"

namespace assembler::log_level_api::metadata_injector {

using TLogApiMetadataScalarValue = std::variant<
    std::monostate,
    std::string,
    std::int64_t,
    std::uint64_t,
    double,
    bool
>;

struct TLogApiMetadataFieldValue final {
    TLogApiMetadataFieldId field_id{};
    TLogApiMetadataFieldValueKind value_kind{TLogApiMetadataFieldValueKind::Unknown};
    TLogApiMetadataScalarValue value{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return field_id.IsValid()
            && value_kind != TLogApiMetadataFieldValueKind::Unknown
            && !std::holds_alternative<std::monostate>(value);
    }
};

} // namespace assembler::log_level_api::metadata_injector

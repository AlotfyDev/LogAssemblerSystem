#pragma once

/*
    LOGAPI-W11 — Default C-Style Struct Primitive Schemas

    This header belongs to the default C-style struct primitive content schema
    add-on pack.

    Responsibility:
        Define ABI/layout-sensitive primitive struct schema descriptors,
        fixed-width primitive field descriptors, explicit offsets, sizes,
        alignment, padding, endianness, presence/default flags, and level-specific
        primitive struct schema profiles.

    Boundary:
        This wave defines C-style struct primitive schema descriptors only.
        It must not implement binary parsing, concrete validators, metadata structs,
        timestamp stabilization, envelope assembly, API facade hot-path behavior,
        circulation bindings, or policy assignment.

    Doctrine:
        C-style struct schemas must be layout-specified, not compiler-implied.
        Defaults are bundled conveniences, not a closed content universe.
*/

#include <string>

#include "TLogApiDefaultCStructSchemaPack.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

class TLogApiDefaultCStructSchemaFactory final {
private:
    [[nodiscard]] static TLogApiCStructFieldDescriptor RequiredField(
        std::uint64_t id,
        const char* name,
        TLogApiCStructPrimitiveKind primitive,
        std::uint32_t offset,
        std::uint32_t size,
        std::uint32_t alignment = 1
    ) {
        TLogApiCStructFieldDescriptor f{};
        f.id = TLogApiCStructFieldId{id};
        f.field_name = name;
        f.presence = TLogApiCStructFieldPresenceKind::Required;
        f.layout.offset_bytes = offset;
        f.layout.size_bytes = size;
        f.layout.alignment_bytes = alignment;
        f.layout.primitive_kind = primitive;
        return f;
    }

    [[nodiscard]] static TLogApiCStructFieldDescriptor OptionalField(
        std::uint64_t id,
        const char* name,
        TLogApiCStructPrimitiveKind primitive,
        std::uint32_t offset,
        std::uint32_t size,
        std::uint32_t alignment = 1
    ) {
        TLogApiCStructFieldDescriptor f = RequiredField(id, name, primitive, offset, size, alignment);
        f.presence = TLogApiCStructFieldPresenceKind::Optional;
        return f;
    }

    [[nodiscard]] static TLogApiCStructFieldDescriptor DefaultedLevelField(
        TLogApiCStructLogLevelKind level,
        std::uint32_t offset
    ) {
        TLogApiCStructFieldDescriptor f{};
        f.id = TLogApiCStructFieldId{2};
        f.field_name = "level_code";
        f.presence = TLogApiCStructFieldPresenceKind::Defaulted;
        f.layout.offset_bytes = offset;
        f.layout.size_bytes = 1;
        f.layout.alignment_bytes = 1;
        f.layout.primitive_kind = TLogApiCStructPrimitiveKind::UInt8;
        f.default_value.primitive_kind = TLogApiCStructPrimitiveKind::UInt8;
        f.default_value.value = static_cast<std::uint64_t>(level);
        f.override_allowed = false;
        return f;
    }

    [[nodiscard]] static TLogApiCStructFieldDescriptor ReservedField(
        std::uint64_t id,
        const char* name,
        std::uint32_t offset,
        std::uint32_t size
    ) {
        TLogApiCStructFieldDescriptor f{};
        f.id = TLogApiCStructFieldId{id};
        f.field_name = name;
        f.presence = TLogApiCStructFieldPresenceKind::Reserved;
        f.layout.offset_bytes = offset;
        f.layout.size_bytes = size;
        f.layout.alignment_bytes = 1;
        f.layout.primitive_kind = TLogApiCStructPrimitiveKind::UInt8;
        return f;
    }

    [[nodiscard]] static TLogApiCStructLevelSchemaDescriptor MakeLevelSchema(
        std::uint64_t schema_id,
        TLogApiCStructLogLevelKind level,
        const char* schema_name
    ) {
        /*
            Canonical minimal primitive layout, 128 bytes:

            offset  size  field
            0       2     schema_marker       required UInt16
            2       1     level_code          defaulted UInt8
            3       1     flags               optional UInt8
            4       4     message_id          required UInt32
            8       8     numeric_code        optional Int64
            16      8     payload_timestamp   optional Int64, source-provided only
            24      104   reserved            reserved bytes

            Metadata is not here.
            Stabilized timestamp is not here.
        */
        TLogApiCStructLevelSchemaDescriptor schema{};
        schema.id = TLogApiCStructSchemaId{schema_id};
        schema.level = level;
        schema.schema_name = schema_name;
        schema.schema_version = "v1";
        schema.layout.total_size_bytes = 128;
        schema.layout.alignment_bytes = 8;
        schema.layout.endian = TLogApiCStructEndianKind::LittleEndian;
        schema.layout.fields = {
            RequiredField(1, "schema_marker", TLogApiCStructPrimitiveKind::UInt16, 0, 2, 2),
            DefaultedLevelField(level, 2),
            OptionalField(3, "flags", TLogApiCStructPrimitiveKind::UInt8, 3, 1, 1),
            RequiredField(4, "message_id", TLogApiCStructPrimitiveKind::UInt32, 4, 4, 4),
            OptionalField(5, "numeric_code", TLogApiCStructPrimitiveKind::Int64, 8, 8, 8),
            OptionalField(6, "payload_timestamp", TLogApiCStructPrimitiveKind::Int64, 16, 8, 8),
            ReservedField(7, "reserved", 24, 104)
        };
        return schema;
    }

public:
    [[nodiscard]] static TLogApiDefaultCStructSchemaPack MakeDefaultPack() {
        TLogApiDefaultCStructSchemaPack pack{};
        pack.id = TLogApiCStructSchemaPackId{1};
        pack.pack_name = "default.logapi.cstruct.primitive.schema.pack";
        pack.pack_version = "v1";
        pack.schemas = {
            MakeLevelSchema(1, TLogApiCStructLogLevelKind::Trace,    "default.cstruct.trace"),
            MakeLevelSchema(2, TLogApiCStructLogLevelKind::Debug,    "default.cstruct.debug"),
            MakeLevelSchema(3, TLogApiCStructLogLevelKind::Info,     "default.cstruct.info"),
            MakeLevelSchema(4, TLogApiCStructLogLevelKind::Notice,   "default.cstruct.notice"),
            MakeLevelSchema(5, TLogApiCStructLogLevelKind::Warning,  "default.cstruct.warning"),
            MakeLevelSchema(6, TLogApiCStructLogLevelKind::Error,    "default.cstruct.error"),
            MakeLevelSchema(7, TLogApiCStructLogLevelKind::Critical, "default.cstruct.critical"),
            MakeLevelSchema(8, TLogApiCStructLogLevelKind::Fatal,    "default.cstruct.fatal")
        };
        return pack;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives

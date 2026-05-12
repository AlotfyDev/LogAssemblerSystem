#pragma once

/*
    LOGAPI-W10 — Default JSON Content Schemas

    This header belongs to the default JSON content schema add-on pack.

    Responsibility:
        Define default JSON content schema descriptors, JSON field descriptors,
        required field sets, default field values, and level-specific default
        JSON schema profiles.

    Boundary:
        This wave defines JSON schema descriptors only.
        It must not implement concrete JSON parsing, concrete validators, metadata
        structs, timestamp stabilization, envelope assembly, API facade hot-path
        behavior, circulation bindings, or policy assignment.

    Doctrine:
        Default JSON schemas are bundled conveniences, not a closed content universe.
        The consuming API still receives content only.
*/

#include <string>

#include "TLogApiDefaultJsonSchemaPack.hpp"

namespace assembler::log_level_api::content::json_schemas {

class TLogApiDefaultJsonSchemaFactory final {
private:
    [[nodiscard]] static TLogApiJsonFieldDescriptor RequiredString(
        std::uint64_t id,
        const char* name
    ) {
        TLogApiJsonFieldDescriptor f{};
        f.id = TLogApiJsonFieldId{id};
        f.field_name = name;
        f.value_kind = TLogApiJsonFieldValueKind::String;
        f.presence = TLogApiJsonFieldPresenceKind::Required;
        return f;
    }

    [[nodiscard]] static TLogApiJsonFieldDescriptor OptionalString(
        std::uint64_t id,
        const char* name
    ) {
        TLogApiJsonFieldDescriptor f{};
        f.id = TLogApiJsonFieldId{id};
        f.field_name = name;
        f.value_kind = TLogApiJsonFieldValueKind::String;
        f.presence = TLogApiJsonFieldPresenceKind::Optional;
        return f;
    }

    [[nodiscard]] static TLogApiJsonFieldDescriptor DefaultString(
        std::uint64_t id,
        const char* name,
        const char* value,
        bool override_allowed = true
    ) {
        TLogApiJsonFieldDescriptor f{};
        f.id = TLogApiJsonFieldId{id};
        f.field_name = name;
        f.value_kind = TLogApiJsonFieldValueKind::String;
        f.presence = TLogApiJsonFieldPresenceKind::Defaulted;
        f.default_value.value_kind = TLogApiJsonFieldValueKind::String;
        f.default_value.value = std::string{value};
        f.override_allowed = override_allowed;
        return f;
    }

    [[nodiscard]] static TLogApiJsonLevelSchemaDescriptor MakeLevelSchema(
        std::uint64_t schema_id,
        TLogApiLogLevelKind level,
        const char* schema_name,
        const char* default_level_text
    ) {
        TLogApiJsonLevelSchemaDescriptor schema{};
        schema.id = TLogApiJsonSchemaId{schema_id};
        schema.level = level;
        schema.schema_name = schema_name;
        schema.schema_version = "v1";
        schema.unknown_field_policy = TLogApiJsonUnknownFieldPolicy::PreserveButDoNotValidate;

        /*
            Minimal hot-path-friendly payload:
                message is required.
                level is defaulted by the schema.
                code/context/payload_timestamp are optional source payload fields.

            Metadata fields are not here.
            Stabilized timestamp is not here.
        */
        schema.fields.fields = {
            RequiredString(1, "message"),
            DefaultString(2, "level", default_level_text, false),
            OptionalString(3, "code"),
            OptionalString(4, "context"),
            OptionalString(5, "payload_timestamp")
        };
        return schema;
    }

public:
    [[nodiscard]] static TLogApiDefaultJsonSchemaPack MakeDefaultPack() {
        TLogApiDefaultJsonSchemaPack pack{};
        pack.id = TLogApiJsonSchemaPackId{1};
        pack.pack_name = "default.logapi.json.schema.pack";
        pack.pack_version = "v1";
        pack.schemas = {
            MakeLevelSchema(1, TLogApiLogLevelKind::Trace,    "default.json.trace",    "trace"),
            MakeLevelSchema(2, TLogApiLogLevelKind::Debug,    "default.json.debug",    "debug"),
            MakeLevelSchema(3, TLogApiLogLevelKind::Info,     "default.json.info",     "info"),
            MakeLevelSchema(4, TLogApiLogLevelKind::Notice,   "default.json.notice",   "notice"),
            MakeLevelSchema(5, TLogApiLogLevelKind::Warning,  "default.json.warning",  "warning"),
            MakeLevelSchema(6, TLogApiLogLevelKind::Error,    "default.json.error",    "error"),
            MakeLevelSchema(7, TLogApiLogLevelKind::Critical, "default.json.critical", "critical"),
            MakeLevelSchema(8, TLogApiLogLevelKind::Fatal,    "default.json.fatal",    "fatal")
        };
        return pack;
    }
};

} // namespace assembler::log_level_api::content::json_schemas

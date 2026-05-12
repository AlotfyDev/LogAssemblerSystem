#pragma once

/*
    LOGAPI-W20 — Metadata Default Field Packs

    Responsibility:
        Define default metadata field packs and helpers for composing reusable
        metadata field/value groups into metadata profile configurations.

    Boundary:
        Metadata field packs are configuration conveniences, not policy objects.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff,
        persistence, or policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Default field packs reduce repeated per-call payload authoring.
        Metadata values remain mutable through profile/update surfaces.
*/

#include <string>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldDescriptor.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldId.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldValue.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldValueKind.hpp"

#include "TLogApiMetadataDefaultFieldPackSet.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

class TLogApiMetadataDefaultFieldPackFactory final {
private:
    using Field = assembler::log_level_api::metadata_injector::TLogApiMetadataFieldDescriptor;
    using Value = assembler::log_level_api::metadata_injector::TLogApiMetadataFieldValue;
    using FieldId = assembler::log_level_api::metadata_injector::TLogApiMetadataFieldId;
    using Kind = assembler::log_level_api::metadata_injector::TLogApiMetadataFieldValueKind;

    [[nodiscard]] static Field StringField(std::uint64_t id, const char* name, bool mutable_value = true) {
        Field f{};
        f.id = FieldId{id};
        f.field_name = name;
        f.value_kind = Kind::String;
        f.mutable_value = mutable_value;
        f.enabled = true;
        return f;
    }

    [[nodiscard]] static Field U64Field(std::uint64_t id, const char* name, bool mutable_value = true) {
        Field f{};
        f.id = FieldId{id};
        f.field_name = name;
        f.value_kind = Kind::UnsignedInteger;
        f.mutable_value = mutable_value;
        f.enabled = true;
        return f;
    }

    [[nodiscard]] static Value StringValue(std::uint64_t id, const char* value) {
        return Value{FieldId{id}, Kind::String, std::string{value}};
    }

    [[nodiscard]] static Value U64Value(std::uint64_t id, std::uint64_t value) {
        return Value{FieldId{id}, Kind::UnsignedInteger, value};
    }

public:
    [[nodiscard]] static TLogApiMetadataDefaultFieldPack MakeSchemaIdentityPack() {
        TLogApiMetadataDefaultFieldPack pack{};
        pack.id = TLogApiMetadataFieldPackId{1};
        pack.kind = TLogApiMetadataFieldPackKind::SchemaIdentity;
        pack.status = TLogApiMetadataFieldPackStatus::Active;
        pack.pack_name = "default.metadata.schema_identity";
        pack.fields = {
            StringField(1, "schema_id"),
            StringField(2, "schema_family"),
            StringField(3, "schema_version"),
            StringField(4, "schema_kind")
        };
        pack.values.values = {
            StringValue(1, "default.logapi.schema"),
            StringValue(2, "logapi.default"),
            StringValue(3, "v1"),
            StringValue(4, "metadata")
        };
        return pack;
    }

    [[nodiscard]] static TLogApiMetadataDefaultFieldPack MakeSourceIdentityPack() {
        TLogApiMetadataDefaultFieldPack pack{};
        pack.id = TLogApiMetadataFieldPackId{2};
        pack.kind = TLogApiMetadataFieldPackKind::SourceIdentity;
        pack.status = TLogApiMetadataFieldPackStatus::Active;
        pack.pack_name = "default.metadata.source_identity";
        pack.fields = {
            StringField(101, "source_name"),
            StringField(102, "component_name"),
            StringField(103, "producer_name"),
            U64Field(104, "producer_instance_id")
        };
        pack.values.values = {
            StringValue(101, "default-source"),
            StringValue(102, "default-component"),
            StringValue(103, "default-producer"),
            U64Value(104, 0)
        };
        return pack;
    }

    [[nodiscard]] static TLogApiMetadataDefaultFieldPack MakeRuntimeContextPack() {
        TLogApiMetadataDefaultFieldPack pack{};
        pack.id = TLogApiMetadataFieldPackId{3};
        pack.kind = TLogApiMetadataFieldPackKind::RuntimeContext;
        pack.status = TLogApiMetadataFieldPackStatus::Active;
        pack.pack_name = "default.metadata.runtime_context";
        pack.fields = {
            StringField(201, "runtime_name"),
            StringField(202, "runtime_version"),
            StringField(203, "host_name"),
            U64Field(204, "process_id")
        };
        pack.values.values = {
            StringValue(201, "default-runtime"),
            StringValue(202, "v1"),
            StringValue(203, "default-host"),
            U64Value(204, 0)
        };
        return pack;
    }

    [[nodiscard]] static TLogApiMetadataDefaultFieldPack MakeCorrelationPack() {
        TLogApiMetadataDefaultFieldPack pack{};
        pack.id = TLogApiMetadataFieldPackId{4};
        pack.kind = TLogApiMetadataFieldPackKind::Correlation;
        pack.status = TLogApiMetadataFieldPackStatus::Active;
        pack.pack_name = "default.metadata.correlation";
        pack.fields = {
            StringField(301, "correlation_id"),
            StringField(302, "causation_id"),
            StringField(303, "trace_id"),
            StringField(304, "span_id")
        };
        pack.values.values = {
            StringValue(301, "none"),
            StringValue(302, "none"),
            StringValue(303, "none"),
            StringValue(304, "none")
        };
        return pack;
    }

    [[nodiscard]] static TLogApiMetadataDefaultFieldPack MakeEnvironmentPack() {
        TLogApiMetadataDefaultFieldPack pack{};
        pack.id = TLogApiMetadataFieldPackId{5};
        pack.kind = TLogApiMetadataFieldPackKind::Environment;
        pack.status = TLogApiMetadataFieldPackStatus::Active;
        pack.pack_name = "default.metadata.environment";
        pack.fields = {
            StringField(401, "environment"),
            StringField(402, "deployment"),
            StringField(403, "region"),
            StringField(404, "tenant")
        };
        pack.values.values = {
            StringValue(401, "default"),
            StringValue(402, "default"),
            StringValue(403, "default"),
            StringValue(404, "default")
        };
        return pack;
    }

    [[nodiscard]] static TLogApiMetadataDefaultFieldPackSet MakeDefaultSet() {
        TLogApiMetadataDefaultFieldPackSet set{};
        set.packs = {
            MakeSchemaIdentityPack(),
            MakeSourceIdentityPack(),
            MakeRuntimeContextPack(),
            MakeCorrelationPack(),
            MakeEnvironmentPack()
        };
        return set;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs

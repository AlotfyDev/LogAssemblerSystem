#include <cassert>
#include <iostream>
#include <string>

#include "assembler/log_level_api/metadata_injector/default_field_packs/TLogApiMetadataDefaultFieldPackSurface.hpp"

int main() {
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::metadata_injector::default_field_packs;

    auto set = TLogApiMetadataDefaultFieldPackFactory::MakeDefaultSet();
    assert(set.IsDeclared());

    auto view = TLogApiMetadataDefaultFieldPackSetView::From(set);
    assert(view.declared);
    assert(view.pack_count == 5);

    const auto* schema_pack = set.Find(TLogApiMetadataFieldPackKind::SchemaIdentity);
    assert(schema_pack != nullptr);
    assert(schema_pack->IsDeclared());
    assert(schema_pack->fields.size() == 4);

    const auto* env_pack = set.Find(TLogApiMetadataFieldPackKind::Environment);
    assert(env_pack != nullptr);
    assert(env_pack->values.Find(TLogApiMetadataFieldId{401}) != nullptr);

    auto composed = TLogApiMetadataFieldPackComposer::Compose(set);
    assert(composed.IsAccepted());
    assert(composed.config.IsReady());
    assert(composed.config.metadata_struct.fields.size() == 20);
    assert(composed.config.default_values.values.size() == 20);

    const auto* schema_version = composed.config.default_values.Find(TLogApiMetadataFieldId{3});
    assert(schema_version != nullptr);
    assert(std::get<std::string>(schema_version->value) == "v1");

    const auto* source_name = composed.config.default_values.Find(TLogApiMetadataFieldId{101});
    assert(source_name != nullptr);
    assert(std::get<std::string>(source_name->value) == "default-source");

    std::cout << "LOGAPI-W20 smoke test passed\\n";
    return 0;
}

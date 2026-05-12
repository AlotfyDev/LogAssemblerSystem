#include <cassert>
#include <iostream>
#include <string>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"

int main() {
    using namespace assembler::log_level_api::metadata_injector;

    auto config = TLogApiDefaultMetadataProfile::Make();
    assert(config.IsReady());

    auto result = TLogApiMetadataInjector::Prepare(config);
    assert(result.IsAccepted());
    assert(result.block.IsReadyForEnvelope());

    auto view = TLogApiMetadataStructView::From(result.block.descriptor);
    assert(view.resolved);
    assert(view.schema_id == "default.logapi.schema");
    assert(view.schema_family == "logapi.default");
    assert(view.schema_version == "v1");
    assert(view.schema_kind == "metadata");
    assert(view.field_names.size() == 4);

    TLogApiMetadataUpdateSet updates{};
    updates.updates.push_back({
        TLogApiMetadataFieldId{3},
        TLogApiMetadataFieldValueKind::String,
        std::string{"v2"}
    });

    auto patched = TLogApiMetadataInjector::Prepare(config, updates);
    assert(patched.IsAccepted());

    const auto* version = patched.block.values.Find(TLogApiMetadataFieldId{3});
    assert(version != nullptr);
    assert(std::get<std::string>(version->value) == "v2");

    std::cout << "LOGAPI-W04 smoke test passed\\n";
    return 0;
}

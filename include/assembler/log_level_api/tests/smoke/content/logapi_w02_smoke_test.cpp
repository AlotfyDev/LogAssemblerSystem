#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;

    auto registry = TLogApiContentProfileResolver::MakeDefaultRegistryView();

    assert(registry.HasReadyProfile("default.json.minimal"));
    assert(registry.HasReadyProfile("default.c_style_struct_primitives.minimal"));

    const auto* json = registry.FindByName("default.json.minimal");
    assert(json != nullptr);
    assert(json->schema_path.IsJsonPath());
    assert(json->validation_required);
    assert(!json->validator_binding_name.empty());

    auto json_view = TLogApiContentProfileView::From(*json);
    assert(json_view.ready_for_configuration_use);
    assert(json_view.schema_path_kind == "json");

    const auto* cstyle = registry.FindByName("default.c_style_struct_primitives.minimal");
    assert(cstyle != nullptr);
    assert(cstyle->schema_path.IsCStyleStructPrimitivePath());
    assert(!cstyle->validation_required);

    auto cstyle_view = TLogApiContentProfileView::From(*cstyle);
    assert(cstyle_view.ready_for_configuration_use);
    assert(cstyle_view.schema_path_kind == "c_style_struct_primitives");

    const char payload[] = "content-only";
    TLogApiContentInputRef ref{payload, sizeof(payload)};
    assert(ref.IsPresent());

    std::cout << "LOGAPI-W02 smoke test passed\\n";
    return 0;
}

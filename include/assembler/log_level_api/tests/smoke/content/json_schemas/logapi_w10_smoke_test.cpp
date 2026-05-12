#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/json_schemas/TLogApiJsonSchemaSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content::json_schemas;

    auto pack = TLogApiDefaultJsonSchemaFactory::MakeDefaultPack();
    assert(pack.IsDeclared());

    auto pack_view = TLogApiJsonSchemaPackView::From(pack);
    assert(pack_view.declared);
    assert(pack_view.schema_count == 8);

    const auto* info = pack.FindByLevel(TLogApiLogLevelKind::Info);
    assert(info != nullptr);
    assert(info->IsDeclared());

    auto info_view = TLogApiJsonLevelSchemaView::From(*info);
    assert(info_view.declared);
    assert(info_view.required_count == 1);
    assert(info_view.defaulted_count == 1);
    assert(info_view.field_count == 5);

    TLogApiJsonSchemaValidationInputDescriptor validator_input{info};
    assert(validator_input.IsReady());
    assert(validator_input.RequiredFieldCount() == 1);
    assert(validator_input.DefaultedFieldCount() == 1);

    const auto* fatal = pack.FindByLevel(TLogApiLogLevelKind::Fatal);
    assert(fatal != nullptr);
    assert(fatal->schema_name == "default.json.fatal");

    std::cout << "LOGAPI-W10 smoke test passed\\n";
    return 0;
}

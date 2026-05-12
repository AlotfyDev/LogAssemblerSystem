#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5ExtendedSchemaSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;

    auto pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    assert(pack.IsDeclared());

    auto view = TLogApiMt5SchemaPackView::From(pack);
    assert(view.declared);
    assert(view.schema_count == 12);

    const auto* tick = pack.Find(TLogApiMt5StructureKind::MqlTick);
    assert(tick != nullptr);
    assert(tick->primary_tick_schema);
    assert(tick->fields.FindByName("bid") != nullptr);
    assert(tick->fields.FindByName("ask") != nullptr);
    assert(tick->fields.FindByName("volume_real") != nullptr);

    auto tick_view = TLogApiMt5StructureSchemaView::From(*tick);
    assert(tick_view.declared);
    assert(tick_view.field_count == 8);

    const auto* request = pack.Find(TLogApiMt5StructureKind::MqlTradeRequest);
    assert(request != nullptr);
    assert(request->fields.FindByName("action") != nullptr);
    assert(request->fields.FindByName("position_by") != nullptr);
    assert(request->fields.fields.size() == 17);

    const auto* calendar_value = pack.Find(TLogApiMt5StructureKind::MqlCalendarValue);
    assert(calendar_value != nullptr);
    assert(calendar_value->fields.FindByName("actual_value") != nullptr);
    assert(calendar_value->fields.FindByName("impact_type") != nullptr);

    TLogApiMt5ValidationInputDescriptor validation{tick};
    assert(validation.IsReady());
    assert(validation.FieldCount() == 8);

    std::cout << "LOGAPI-W12 smoke test passed\\n";
    return 0;
}

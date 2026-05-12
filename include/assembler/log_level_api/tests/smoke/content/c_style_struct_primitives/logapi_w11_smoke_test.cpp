#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructPrimitiveSchemaSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content::c_style_struct_primitives;

    auto pack = TLogApiDefaultCStructSchemaFactory::MakeDefaultPack();
    assert(pack.IsDeclared());

    auto pack_view = TLogApiCStructSchemaPackView::From(pack);
    assert(pack_view.declared);
    assert(pack_view.schema_count == 8);

    const auto* warning = pack.FindByLevel(TLogApiCStructLogLevelKind::Warning);
    assert(warning != nullptr);
    assert(warning->IsDeclared());

    auto warning_view = TLogApiCStructLevelSchemaView::From(*warning);
    assert(warning_view.declared);
    assert(warning_view.total_size_bytes == 128);
    assert(warning_view.alignment_bytes == 8);
    assert(warning_view.required_count == 2); // schema_marker + message_id
    assert(warning_view.defaulted_count == 1); // level_code
    assert(warning_view.field_count == 7);

    TLogApiCStructValidationInputDescriptor validator_input{warning};
    assert(validator_input.IsReady());
    assert(validator_input.TotalSizeBytes() == 128);
    assert(validator_input.RequiredFieldCount() == 2);

    TLogApiCStructCrossLanguageNote note{};
    assert(note.languages.size() == 4);
    assert(!note.rule.empty());

    const auto* fatal = pack.FindByLevel(TLogApiCStructLogLevelKind::Fatal);
    assert(fatal != nullptr);
    assert(fatal->schema_name == "default.cstruct.fatal");
    assert(!fatal->layout.HasOverlappingFields());

    std::cout << "LOGAPI-W11 smoke test passed\\n";
    return 0;
}

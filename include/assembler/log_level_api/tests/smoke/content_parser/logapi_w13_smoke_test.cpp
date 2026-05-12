#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content_parser;

    auto registry = TLogApiDefaultParserProfiles::MakeDefaultRegistryView();
    assert(registry.HasResolvedBinding("default.opaque.no_parse.binding"));

    const auto* binding = registry.FindByName("default.opaque.no_parse.binding");
    assert(binding != nullptr);
    assert(binding->profile.IsOpaqueNoParse());

    auto binding_view = TLogApiContentParserBindingView::From(*binding);
    assert(binding_view.resolved);
    assert(binding_view.opaque_no_parse);
    assert(binding_view.parser_kind == "opaque_no_parse");

    const char payload[] = "opaque-content";
    TLogApiContentInputRef content{payload, sizeof(payload)};

    TLogApiContentParseRequest request{};
    request.content = content;
    request.parser_binding = binding;
    assert(request.IsReady());

    auto result = TLogApiOpaqueContentParser::Parse(request);
    assert(result.IsAccepted());
    assert(result.parsed_content.IsOpaque());
    assert(!result.parsed_content.parsed);
    assert(result.parsed_content.source_content.size_bytes == sizeof(payload));

    auto parsed_view = TLogApiParsedContentView::From(result.parsed_content);
    assert(parsed_view.opaque);
    assert(parsed_view.source_present);
    assert(parsed_view.parsed_kind == "opaque_content_ref");

    std::cout << "LOGAPI-W13 smoke test passed\\n";
    return 0;
}

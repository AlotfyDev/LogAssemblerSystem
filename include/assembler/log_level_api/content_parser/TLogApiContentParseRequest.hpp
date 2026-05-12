#pragma once

/*
    LOGAPI-W13 — Content Parser Core And Binding Surface

    Responsibility:
        Define the core content parser contract, parser binding surface, parser
        profile, parser result model, parsed content references/views, parser
        capabilities, and the opaque/no-parse profile.

    Boundary:
        This wave does not implement concrete JSON parsers, concrete C-style
        struct primitive parsers, MT5 parsers, concrete validators, metadata
        injection, timestamp stabilization, envelope assembly, circulation
        binding, or policy assignment.

    Doctrine:
        Parser selection is configuration-time.
        Parser execution is hot-path.
        Parser discovery is never hot-path.
        Opaque/NoParse is a first-class profile.
*/

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"

#include "TLogApiContentParserBindingDescriptor.hpp"

namespace assembler::log_level_api::content_parser {

/*
    Parse request.

    The request carries content and an already resolved parser binding.
    It must not carry schema definitions, metadata structs, timestamp rules, or
    validator bindings.
*/
struct TLogApiContentParseRequest final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};
    const TLogApiContentParserBindingDescriptor* parser_binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return content.IsPresent()
            && parser_binding != nullptr
            && parser_binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser

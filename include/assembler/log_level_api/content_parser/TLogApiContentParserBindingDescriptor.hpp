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

#include <string>

#include "TLogApiContentParserProfile.hpp"

namespace assembler::log_level_api::content_parser {

/*
    Configuration-time parser binding descriptor.

    This binds an already selected content profile/schema to a parser profile.
    It does not instantiate concrete parsers.
*/
struct TLogApiContentParserBindingDescriptor final {
    std::string binding_name{};
    TLogApiContentParserProfile profile{};

    [[nodiscard]] bool IsResolved() const noexcept {
        return !binding_name.empty() && profile.IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser

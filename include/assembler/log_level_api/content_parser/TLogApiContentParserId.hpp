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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content_parser {

struct TLogApiContentParserId final {
    std::uint64_t value{0};

    constexpr TLogApiContentParserId() = default;
    constexpr explicit TLogApiContentParserId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-content-parser-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::content_parser

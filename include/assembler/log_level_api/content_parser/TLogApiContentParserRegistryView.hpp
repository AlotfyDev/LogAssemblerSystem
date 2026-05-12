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
#include <vector>

#include "TLogApiContentParserBindingDescriptor.hpp"

namespace assembler::log_level_api::content_parser {

/*
    Read-only parser binding registry view.

    This is not a runtime service locator. It is a configuration-time registry view.
*/
struct TLogApiContentParserRegistryView final {
    std::vector<TLogApiContentParserBindingDescriptor> bindings{};

    [[nodiscard]] const TLogApiContentParserBindingDescriptor* FindByName(const std::string& name) const noexcept {
        for (const auto& binding : bindings) {
            if (binding.binding_name == name) return &binding;
        }
        return nullptr;
    }

    [[nodiscard]] bool HasResolvedBinding(const std::string& name) const noexcept {
        const auto* binding = FindByName(name);
        return binding != nullptr && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser

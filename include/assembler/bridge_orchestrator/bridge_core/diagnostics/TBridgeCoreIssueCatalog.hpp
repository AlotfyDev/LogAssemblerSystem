#pragma once
#include <string_view>

namespace assembler::communication_context
{
    struct TBridgeCoreIssueCatalog final
    {
        [[nodiscard]] static constexpr std::string_view invalid_bridge() noexcept { return "bridge.invalid"; }
        [[nodiscard]] static constexpr std::string_view invalid_config() noexcept { return "bridge.config.invalid"; }
        [[nodiscard]] static constexpr std::string_view invalid_protocol() noexcept { return "bridge.protocol.invalid"; }
        [[nodiscard]] static constexpr std::string_view budget_exhausted() noexcept { return "bridge.budget.exhausted"; }
        [[nodiscard]] static constexpr std::string_view protocol_step_failed() noexcept { return "bridge.protocol.step_failed"; }
    };
}

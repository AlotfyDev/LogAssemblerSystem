#pragma once

/*
    LOGAPI-W26 — Circulation Integration Smoke Skeleton

    Responsibility:
        Define a minimal smoke-level integration skeleton that connects a ready
        Log Level API envelope exposure and the W25 circulation handoff contract
        to a stub circulation admission result.

    Boundary:
        This wave does not implement the circulation engine, placement, slots,
        queues, waiting lists, round managers, dispatcher, bridge orchestration,
        protocols, or real admission behavior.

    Doctrine:
        This is an integration skeleton, not production circulation.
        It proves boundary compatibility only.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiCirculationIntegrationId final {
    std::uint64_t value{0};

    constexpr TLogApiCirculationIntegrationId() = default;
    constexpr explicit TLogApiCirculationIntegrationId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-circulation-integration-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration

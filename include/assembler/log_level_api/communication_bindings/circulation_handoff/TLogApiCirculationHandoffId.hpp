#pragma once

/*
    LOGAPI-W25 — Circulation Handoff Contract

    Responsibility:
        Define the handoff contract from Log Level API envelope exposure toward
        the future circulation intake/admission surface.

    Boundary:
        This wave defines request/result/admission contract carriers only.
        It does not implement circulation engine behavior, placement, slots,
        queues, waiting lists, bridge orchestration, protocol execution, envelope
        assembly, validators, timestamp stabilization, metadata injection, or
        policy assignment.

    Doctrine:
        Log Level API exposes a ready envelope.
        Circulation owns admission and placement.
        This contract bridges readiness to future circulation intake without
        leaking circulation internals into Log Level API.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

struct TLogApiCirculationHandoffId final {
    std::uint64_t value{0};

    constexpr TLogApiCirculationHandoffId() = default;
    constexpr explicit TLogApiCirculationHandoffId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-circulation-handoff-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff

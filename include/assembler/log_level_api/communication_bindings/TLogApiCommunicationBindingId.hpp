#pragma once

/*
    LOGAPI-W09 — Communication Bindings To Circulation

    This header belongs to the Log Level API communication-binding layer.

    Responsibility:
        Define the binding surface between the Log Level API side and the
        Circulation side.

        The Log Level API side is represented by a content-provider plugin adapter.
        The Circulation side is represented by a circulation intake/admission port
        adapter descriptor.

    Boundary:
        This wave does not implement circulation engine behavior, bridge
        orchestration, sessions, protocols, content schemas, validators, metadata
        injection, timestamp stabilization, envelope assembly, or policy assignment.

    Doctrine:
        Log Level API produces an assembled envelope.
        Circulation admits the envelope through its own port surface.
        Communication binding describes compatibility and handoff readiness only.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::communication_bindings {

struct TLogApiCommunicationBindingId final {
    std::uint64_t value{0};

    constexpr TLogApiCommunicationBindingId() = default;
    constexpr explicit TLogApiCommunicationBindingId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-circulation-binding-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::communication_bindings

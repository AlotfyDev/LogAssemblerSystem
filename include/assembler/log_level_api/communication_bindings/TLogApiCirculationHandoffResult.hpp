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

#include <string>

#include "TLogApiCirculationHandoffStatus.hpp"

namespace assembler::log_level_api::communication_bindings {

struct TLogApiCirculationHandoffResult final {
    TLogApiCirculationHandoffStatus status{TLogApiCirculationHandoffStatus::Unknown};
    std::string message{};

    [[nodiscard]] bool IsAccepted() const noexcept {
        return status == TLogApiCirculationHandoffStatus::AcceptedByBinding;
    }
};

} // namespace assembler::log_level_api::communication_bindings

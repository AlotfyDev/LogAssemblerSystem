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

#include "TLogApiCirculationPortAdapterId.hpp"
#include "TLogApiCirculationPortAdapterStatus.hpp"

namespace assembler::log_level_api::communication_bindings {

/*
    Circulation side of the binding.

    This descriptor represents the port adapter surface that can admit a Log API
    envelope into the circulation mechanism/engine. It does not implement the
    circulation engine.
*/
struct TLogApiCirculationPortAdapterDescriptor final {
    TLogApiCirculationPortAdapterId id{};
    TLogApiCirculationPortAdapterStatus status{TLogApiCirculationPortAdapterStatus::Unknown};

    std::string port_name{};
    std::string accepted_material_kind{"logapi.envelope"};
    std::string intake_profile_name{};

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && (status == TLogApiCirculationPortAdapterStatus::Resolved
                || status == TLogApiCirculationPortAdapterStatus::Ready)
            && !port_name.empty()
            && !accepted_material_kind.empty()
            && !intake_profile_name.empty();
    }
};

} // namespace assembler::log_level_api::communication_bindings

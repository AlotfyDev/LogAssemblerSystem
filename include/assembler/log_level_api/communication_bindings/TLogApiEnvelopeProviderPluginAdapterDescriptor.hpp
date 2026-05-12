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

#include "TLogApiEnvelopeProviderPluginAdapterId.hpp"
#include "TLogApiProviderAdapterStatus.hpp"

namespace assembler::log_level_api::communication_bindings {

/*
    Log Level API side of the binding.

    This descriptor represents a provider plugin adapter capable of exposing an
    assembled Log Level Envelope to a circulation intake/admission port.
*/
struct TLogApiEnvelopeProviderPluginAdapterDescriptor final {
    TLogApiEnvelopeProviderPluginAdapterId id{};
    TLogApiProviderAdapterStatus status{TLogApiProviderAdapterStatus::Unknown};

    std::string adapter_name{};
    std::string provided_material_kind{"logapi.envelope"};
    std::string provided_profile_name{};

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && (status == TLogApiProviderAdapterStatus::Resolved
                || status == TLogApiProviderAdapterStatus::Ready)
            && !adapter_name.empty()
            && !provided_material_kind.empty()
            && !provided_profile_name.empty();
    }
};

} // namespace assembler::log_level_api::communication_bindings

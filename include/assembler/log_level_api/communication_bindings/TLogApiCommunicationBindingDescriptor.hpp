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

#include "TLogApiCirculationPortAdapterDescriptor.hpp"
#include "TLogApiCommunicationBindingId.hpp"
#include "TLogApiCommunicationBindingStatus.hpp"
#include "TLogApiEnvelopeProviderPluginAdapterDescriptor.hpp"

namespace assembler::log_level_api::communication_bindings {

struct TLogApiCommunicationBindingDescriptor final {
    TLogApiCommunicationBindingId id{};
    TLogApiCommunicationBindingStatus status{TLogApiCommunicationBindingStatus::Unknown};

    std::string binding_name{};
    TLogApiEnvelopeProviderPluginAdapterDescriptor provider{};
    TLogApiCirculationPortAdapterDescriptor circulation_port{};

    [[nodiscard]] bool IsResolved() const noexcept {
        return id.IsValid()
            && (status == TLogApiCommunicationBindingStatus::Resolved
                || status == TLogApiCommunicationBindingStatus::Bound
                || status == TLogApiCommunicationBindingStatus::Ready)
            && !binding_name.empty()
            && provider.IsReady()
            && circulation_port.IsReady()
            && provider.provided_material_kind == circulation_port.accepted_material_kind;
    }
};

} // namespace assembler::log_level_api::communication_bindings

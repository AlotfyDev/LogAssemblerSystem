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

#include "TLogApiCommunicationBindingDescriptor.hpp"

namespace assembler::log_level_api::communication_bindings {

struct TLogApiDefaultCommunicationBindingProfile final {
    [[nodiscard]] static TLogApiCommunicationBindingDescriptor Make() {
        TLogApiEnvelopeProviderPluginAdapterDescriptor provider{};
        provider.id = TLogApiEnvelopeProviderPluginAdapterId{1};
        provider.status = TLogApiProviderAdapterStatus::Resolved;
        provider.adapter_name = "default.logapi.envelope.provider.plugin_adapter";
        provider.provided_material_kind = "logapi.envelope";
        provider.provided_profile_name = "default.envelope.profile";

        TLogApiCirculationPortAdapterDescriptor port{};
        port.id = TLogApiCirculationPortAdapterId{1};
        port.status = TLogApiCirculationPortAdapterStatus::Resolved;
        port.port_name = "default.circulation.envelope.intake.port_adapter";
        port.accepted_material_kind = "logapi.envelope";
        port.intake_profile_name = "default.circulation.intake.profile";

        TLogApiCommunicationBindingDescriptor binding{};
        binding.id = TLogApiCommunicationBindingId{1};
        binding.status = TLogApiCommunicationBindingStatus::Resolved;
        binding.binding_name = "default.logapi.to.circulation.binding";
        binding.provider = provider;
        binding.circulation_port = port;
        return binding;
    }
};

} // namespace assembler::log_level_api::communication_bindings

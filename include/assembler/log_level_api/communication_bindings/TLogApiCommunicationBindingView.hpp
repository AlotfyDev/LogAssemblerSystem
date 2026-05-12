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

#include "TLogApiCommunicationBindingDescriptor.hpp"

namespace assembler::log_level_api::communication_bindings {

struct TLogApiCommunicationBindingView final {
    std::string binding_id{};
    std::string binding_name{};
    std::string provider_name{};
    std::string port_name{};
    std::string material_kind{};
    bool resolved{false};

    [[nodiscard]] static TLogApiCommunicationBindingView From(const TLogApiCommunicationBindingDescriptor& d) {
        TLogApiCommunicationBindingView v{};
        v.binding_id = d.id.ToString();
        v.binding_name = d.binding_name;
        v.provider_name = d.provider.adapter_name;
        v.port_name = d.circulation_port.port_name;
        v.material_kind = d.provider.provided_material_kind;
        v.resolved = d.IsResolved();
        return v;
    }
};

} // namespace assembler::log_level_api::communication_bindings

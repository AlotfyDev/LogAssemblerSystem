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

#include "TLogApiCirculationHandoffRequest.hpp"
#include "TLogApiCirculationHandoffResult.hpp"
#include "TLogApiCommunicationBindingCompatibility.hpp"
#include "TLogApiCommunicationBindingDescriptor.hpp"
#include "TLogApiCommunicationBindingIssue.hpp"
#include "TLogApiCommunicationBindingReport.hpp"
#include "TLogApiCommunicationBindingStatus.hpp"
#include "TLogApiCommunicationBindingView.hpp"

namespace assembler::log_level_api::communication_bindings {

/*
    Binding-level handoff gate.

    This type checks that a complete envelope exists and that the provider/port
    binding is ready. It does not perform circulation admission.
*/
class TLogApiCommunicationBinding final {
public:
    [[nodiscard]] static TLogApiCommunicationBindingReport Inspect(
        const TLogApiCommunicationBindingDescriptor& descriptor
    ) {
        TLogApiCommunicationBindingReport report{};
        report.view = TLogApiCommunicationBindingView::From(descriptor);

        if (!descriptor.IsResolved()) {
            report.issues.push_back({
                "LOGAPI_CIRCULATION_BINDING_NOT_RESOLVED",
                "Provider plugin adapter and circulation port adapter must be resolved and compatible.",
                true
            });
        }

        return report;
    }

    [[nodiscard]] static TLogApiCirculationHandoffResult PrepareHandoff(
        const TLogApiCommunicationBindingDescriptor& descriptor,
        const TLogApiCirculationHandoffRequest& request
    ) {
        if (!descriptor.IsResolved()) {
            return {TLogApiCirculationHandoffStatus::RejectedByBinding, "Binding is not resolved."};
        }

        if (!request.HasEnvelope()) {
            return {TLogApiCirculationHandoffStatus::RejectedByBinding, "A complete envelope is required for handoff."};
        }

        return {TLogApiCirculationHandoffStatus::AcceptedByBinding, "Envelope accepted by binding surface for circulation-side admission."};
    }
};

} // namespace assembler::log_level_api::communication_bindings

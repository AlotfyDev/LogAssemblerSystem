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

#include <vector>

#include "TLogApiCommunicationBindingIssue.hpp"
#include "TLogApiCommunicationBindingView.hpp"

namespace assembler::log_level_api::communication_bindings {

struct TLogApiCommunicationBindingReport final {
    TLogApiCommunicationBindingView view{};
    std::vector<TLogApiCommunicationBindingIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }
};

} // namespace assembler::log_level_api::communication_bindings

#pragma once

/*
    LOGAPI-W26 — Circulation Integration Smoke Skeleton

    Responsibility:
        Define a minimal smoke-level integration skeleton that connects a ready
        Log Level API envelope exposure and the W25 circulation handoff contract
        to a stub circulation admission result.

    Boundary:
        This wave does not implement the circulation engine, placement, slots,
        queues, waiting lists, round managers, dispatcher, bridge orchestration,
        protocols, or real admission behavior.

    Doctrine:
        This is an integration skeleton, not production circulation.
        It proves boundary compatibility only.
*/

#include <string>

#include "TLogApiCirculationSmokeAdmissionStatus.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

/*
    Stub circulation admission result.

    This is not a real circulation placement/admission result. It exists only to
    prove that Log Level API can hand a contract-accepted envelope toward a future
    circulation boundary.
*/
struct TLogApiCirculationSmokeAdmissionResult final {
    TLogApiCirculationSmokeAdmissionStatus status{TLogApiCirculationSmokeAdmissionStatus::Unknown};
    std::string stub_admission_ref{};
    std::string note{};

    [[nodiscard]] bool IsStubAdmitted() const noexcept {
        return status == TLogApiCirculationSmokeAdmissionStatus::StubAdmitted
            && !stub_admission_ref.empty();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration

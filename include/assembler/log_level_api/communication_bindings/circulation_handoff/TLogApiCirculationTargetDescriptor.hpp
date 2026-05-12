#pragma once

/*
    LOGAPI-W25 — Circulation Handoff Contract

    Responsibility:
        Define the handoff contract from Log Level API envelope exposure toward
        the future circulation intake/admission surface.

    Boundary:
        This wave defines request/result/admission contract carriers only.
        It does not implement circulation engine behavior, placement, slots,
        queues, waiting lists, bridge orchestration, protocol execution, envelope
        assembly, validators, timestamp stabilization, metadata injection, or
        policy assignment.

    Doctrine:
        Log Level API exposes a ready envelope.
        Circulation owns admission and placement.
        This contract bridges readiness to future circulation intake without
        leaking circulation internals into Log Level API.
*/

#include <string>

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

/*
    Circulation-side target descriptor.

    This is a descriptor only. It is not a circulation queue, slot, container,
    waiting list, round manager, or dispatcher.
*/
struct TLogApiCirculationTargetDescriptor final {
    std::string target_name{"default.circulation.intake"};
    std::string intake_profile_name{"default.circulation.envelope.intake"};
    std::string accepted_material_kind{"logapi.final_envelope"};
    bool resolved{false};

    [[nodiscard]] bool IsResolved() const noexcept {
        return resolved
            && !target_name.empty()
            && !intake_profile_name.empty()
            && !accepted_material_kind.empty();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff

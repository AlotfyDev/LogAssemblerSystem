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

#include "TLogApiCirculationHandoffRequest.hpp"
#include "TLogApiCirculationHandoffResult.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

struct TLogApiCirculationHandoffView final {
    std::string handoff_id{};
    std::string envelope_id{};
    std::string target_name{};
    std::string intake_profile_name{};
    std::string token{};
    bool request_ready{false};
    bool accepted_by_contract{false};

    [[nodiscard]] static TLogApiCirculationHandoffView From(
        const TLogApiCirculationHandoffRequest& request,
        const TLogApiCirculationHandoffResult& result
    ) {
        TLogApiCirculationHandoffView view{};
        view.handoff_id = request.id.ToString();
        view.envelope_id = request.envelope_exposure.envelope_id;
        view.target_name = request.target.target_name;
        view.intake_profile_name = request.target.intake_profile_name;
        view.token = result.token.ToString();
        view.request_ready = request.IsReady();
        view.accepted_by_contract = result.IsAcceptedByContract();
        return view;
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff

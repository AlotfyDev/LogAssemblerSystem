#pragma once

/*
    LOGAPI-EXT-W01 — Public API Full Flow Orchestrator

    Responsibility:
        Define a production-oriented public API orchestration skeleton that
        connects:
            public content-only request
            → parser
            → metadata preparation
            → timestamp stabilization
            → final envelope shaping
            → envelope exposure
            → circulation handoff contract

    Boundary:
        This wave does not implement specialized JSON/C-struct/MT5 parser routing,
        real circulation admission, envelope streaming, persistence, policy
        assignment, bridge orchestration, or external receiver behavior.

    Doctrine:
        Configure first. Consume content only.
        No per-call schema/metadata/validator/timestamp/assembler/circulation/policy
        configuration is allowed.
*/

#include <string>

#include "TLogApiFullFlowRequest.hpp"
#include "TLogApiFullFlowResult.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

struct TLogApiPublicApiFullFlowView final {
    std::string run_id{};
    std::string status{};
    std::string envelope_id{};
    std::string handoff_token{};
    bool accepted{false};

    [[nodiscard]] static TLogApiPublicApiFullFlowView From(
        const TLogApiFullFlowRequest& request,
        const TLogApiFullFlowResult& result
    ) {
        TLogApiPublicApiFullFlowView view{};
        view.run_id = request.run_id.ToString();
        view.envelope_id = result.envelope_result.envelope.header.id.ToString();
        view.handoff_token = result.handoff_result.token.ToString();
        view.accepted = result.IsAccepted();

        switch (result.status) {
            case TLogApiFullFlowStatus::Parsed: view.status = "parsed"; break;
            case TLogApiFullFlowStatus::MetadataPrepared: view.status = "metadata_prepared"; break;
            case TLogApiFullFlowStatus::TimestampStabilized: view.status = "timestamp_stabilized"; break;
            case TLogApiFullFlowStatus::EnvelopeShaped: view.status = "envelope_shaped"; break;
            case TLogApiFullFlowStatus::EnvelopeExposed: view.status = "envelope_exposed"; break;
            case TLogApiFullFlowStatus::HandoffAccepted: view.status = "handoff_accepted"; break;
            case TLogApiFullFlowStatus::Rejected: view.status = "rejected"; break;
            default: view.status = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator

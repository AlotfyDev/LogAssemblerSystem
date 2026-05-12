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

#include "TLogApiFinalEnvelopeBuilderForPublicFlow.hpp"
#include "TLogApiFullFlowIssue.hpp"
#include "TLogApiFullFlowRequest.hpp"
#include "TLogApiFullFlowResolvedContext.hpp"
#include "TLogApiFullFlowResult.hpp"
#include "TLogApiFullFlowRunId.hpp"
#include "TLogApiFullFlowStatus.hpp"
#include "TLogApiPublicApiFullFlowOrchestrator.hpp"
#include "TLogApiPublicApiFullFlowReport.hpp"
#include "TLogApiPublicApiFullFlowView.hpp"

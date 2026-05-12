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

#include "TLogApiCirculationIntegrationId.hpp"
#include "TLogApiCirculationIntegrationIssue.hpp"
#include "TLogApiCirculationIntegrationReport.hpp"
#include "TLogApiCirculationIntegrationSmokeConfig.hpp"
#include "TLogApiCirculationIntegrationSmokeRequest.hpp"
#include "TLogApiCirculationIntegrationSmokeResult.hpp"
#include "TLogApiCirculationIntegrationSmokeSkeleton.hpp"
#include "TLogApiCirculationIntegrationStatus.hpp"
#include "TLogApiCirculationIntegrationView.hpp"
#include "TLogApiCirculationSmokeAdmissionResult.hpp"
#include "TLogApiCirculationSmokeAdmissionStatus.hpp"
#include "TLogApiDefaultCirculationIntegrationSmokeProfile.hpp"

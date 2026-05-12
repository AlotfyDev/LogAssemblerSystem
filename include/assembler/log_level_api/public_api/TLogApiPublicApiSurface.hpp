#pragma once

/*
    LOGAPI-W27 — Public API Surface And Usage Model

    Responsibility:
        Define stable public API call surfaces for content-only usage:
        opaque payload input, JSON input, C-style struct primitive input,
        typed payload references, public result/error models, and usage-facing
        facade entry points.

    Boundary:
        Public API calls must not accept schema definitions, metadata structures,
        validator bindings, timestamp stabilization rules, assembler selection,
        circulation settings, or policy material per call.

    Doctrine:
        Configure first. Consume content only.
        Public API call surfaces are stable front doors over already resolved
        profiles and previously prepared binding/handoff contracts.
*/

#include "TLogApiCStructPayloadRef.hpp"
#include "TLogApiJsonTextRef.hpp"
#include "TLogApiOpaquePayloadRef.hpp"
#include "TLogApiPublicApiCallView.hpp"
#include "TLogApiPublicApiFacade.hpp"
#include "TLogApiPublicApiUsageModel.hpp"
#include "TLogApiPublicCallId.hpp"
#include "TLogApiPublicCallRequest.hpp"
#include "TLogApiPublicCallResult.hpp"
#include "TLogApiPublicCallStatus.hpp"
#include "TLogApiPublicInputKind.hpp"
#include "TLogApiPublicIssue.hpp"
#include "TLogApiPublicIssueSeverity.hpp"
#include "TLogApiPublicResolvedContext.hpp"

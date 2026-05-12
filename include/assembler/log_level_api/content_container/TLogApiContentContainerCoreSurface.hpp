#pragma once

/*
    LOGAPI-W31 — Content Container Core And Batch Parse Model

    Responsibility:
        Define content container references, container shape descriptors,
        batch parse requests/results, parsed content batch references/views,
        and container envelope emission strategy descriptors.

    Boundary:
        This wave does not implement MT5-specific container parsers, JSON batch
        parsers, C-style struct batch parsers, validators, metadata injection,
        timestamp stabilization, envelope assembly, circulation handoff, policy
        assignment, or runtime dispatch.

    Doctrine:
        Container parser selection is configuration-time.
        Container parser execution is hot-path.
        A container parser handles one known container type.
        Element parser handles one known element type.
        No runtime parser dispatch inside the batch loop.
*/

#include "TLogApiBatchEnvelopeStrategyDescriptor.hpp"
#include "TLogApiBatchEnvelopeStrategyKind.hpp"
#include "TLogApiContainerParseIssue.hpp"
#include "TLogApiContainerParseRequest.hpp"
#include "TLogApiContainerParseResult.hpp"
#include "TLogApiContainerParserId.hpp"
#include "TLogApiContainerParserProfile.hpp"
#include "TLogApiContainerParserStatus.hpp"
#include "TLogApiContentContainerElementKind.hpp"
#include "TLogApiContentContainerId.hpp"
#include "TLogApiContentContainerKind.hpp"
#include "TLogApiContentContainerReadiness.hpp"
#include "TLogApiContentContainerRef.hpp"
#include "TLogApiContentContainerShape.hpp"
#include "TLogApiContentContainerView.hpp"
#include "TLogApiParsedContentBatchId.hpp"
#include "TLogApiParsedContentBatchRef.hpp"
#include "TLogApiParsedContentBatchView.hpp"

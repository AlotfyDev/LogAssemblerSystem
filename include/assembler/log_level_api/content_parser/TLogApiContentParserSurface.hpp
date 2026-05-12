#pragma once

/*
    LOGAPI-W13 — Content Parser Core And Binding Surface

    Responsibility:
        Define the core content parser contract, parser binding surface, parser
        profile, parser result model, parsed content references/views, parser
        capabilities, and the opaque/no-parse profile.

    Boundary:
        This wave does not implement concrete JSON parsers, concrete C-style
        struct primitive parsers, MT5 parsers, concrete validators, metadata
        injection, timestamp stabilization, envelope assembly, circulation
        binding, or policy assignment.

    Doctrine:
        Parser selection is configuration-time.
        Parser execution is hot-path.
        Parser discovery is never hot-path.
        Opaque/NoParse is a first-class profile.
*/

#include "TLogApiContentParseRequest.hpp"
#include "TLogApiContentParseResult.hpp"
#include "TLogApiContentParserBindingDescriptor.hpp"
#include "TLogApiContentParserBindingView.hpp"
#include "TLogApiContentParserCapabilityKind.hpp"
#include "TLogApiContentParserCapabilitySet.hpp"
#include "TLogApiContentParserId.hpp"
#include "TLogApiContentParserInputKind.hpp"
#include "TLogApiContentParserIssue.hpp"
#include "TLogApiContentParserKind.hpp"
#include "TLogApiContentParserProfile.hpp"
#include "TLogApiContentParserRegistryView.hpp"
#include "TLogApiContentParserStatus.hpp"
#include "TLogApiDefaultParserProfiles.hpp"
#include "TLogApiOpaqueContentParser.hpp"
#include "TLogApiParsedContentKind.hpp"
#include "TLogApiParsedContentRef.hpp"
#include "TLogApiParsedContentView.hpp"

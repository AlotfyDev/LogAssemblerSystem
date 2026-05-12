#pragma once

/*
    LOGAPI-W14 — Default JSON Level Parsers

    Responsibility:
        Define dedicated JSON parsers for each default Log Level API JSON schema:
        Trace, Debug, Info, Notice, Warning, Error, Critical, and Fatal.

    Boundary:
        This wave implements lightweight default JSON level parser skeletons only.
        It must not implement concrete validators, metadata injection, timestamp
        stabilization, envelope assembly, communication bindings, or policy assignment.

    Hot-path doctrine:
        Each log level has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include "TCriticalJsonContentParser.hpp"
#include "TDebugJsonContentParser.hpp"
#include "TErrorJsonContentParser.hpp"
#include "TFatalJsonContentParser.hpp"
#include "TInfoJsonContentParser.hpp"
#include "TLogApiJsonLevelParserDetail.hpp"
#include "TLogApiJsonLevelParserProfile.hpp"
#include "TLogApiJsonLevelParserProfileFactory.hpp"
#include "TLogApiJsonParseIssue.hpp"
#include "TLogApiJsonParseResult.hpp"
#include "TLogApiJsonParsedContent.hpp"
#include "TLogApiJsonParsedField.hpp"
#include "TNoticeJsonContentParser.hpp"
#include "TTraceJsonContentParser.hpp"
#include "TWarningJsonContentParser.hpp"

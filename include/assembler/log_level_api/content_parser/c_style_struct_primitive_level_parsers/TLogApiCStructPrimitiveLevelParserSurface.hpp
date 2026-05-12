#pragma once

/*
    LOGAPI-W15 — Default C-Style Struct Primitive Level Parsers

    Responsibility:
        Define dedicated parsers for each default C-style struct primitive
        log-level schema: Trace, Debug, Info, Notice, Warning, Error, Critical,
        and Fatal.

    Boundary:
        This wave implements lightweight default C-style struct primitive parser
        skeletons only. It must not implement validators, metadata injection,
        timestamp stabilization, envelope assembly, communication bindings,
        circulation handoff, or policy assignment.

    Hot-path doctrine:
        Each log level has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        C-style struct parsing uses explicit schema offsets and sizes, not
        compiler-implied struct layout.
*/

#include "TCriticalCStructPrimitiveParser.hpp"
#include "TDebugCStructPrimitiveParser.hpp"
#include "TErrorCStructPrimitiveParser.hpp"
#include "TFatalCStructPrimitiveParser.hpp"
#include "TInfoCStructPrimitiveParser.hpp"
#include "TLogApiCStructLevelParserProfile.hpp"
#include "TLogApiCStructLevelParserProfileFactory.hpp"
#include "TLogApiCStructParseIssue.hpp"
#include "TLogApiCStructParseResult.hpp"
#include "TLogApiCStructParsedContent.hpp"
#include "TLogApiCStructParsedField.hpp"
#include "TLogApiCStructPrimitiveParserDetail.hpp"
#include "TNoticeCStructPrimitiveParser.hpp"
#include "TTraceCStructPrimitiveParser.hpp"
#include "TWarningCStructPrimitiveParser.hpp"

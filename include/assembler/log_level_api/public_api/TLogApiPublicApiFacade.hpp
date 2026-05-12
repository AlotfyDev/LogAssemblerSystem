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

#include "assembler/log_level_api/content_parser/TLogApiOpaqueContentParser.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContract.hpp"
#include "TLogApiPublicCallRequest.hpp"
#include "TLogApiPublicCallResult.hpp"

namespace assembler::log_level_api::public_api {

/*
    Public API facade skeleton.

    This skeleton demonstrates stable content-only public API call handling.
    It currently uses the parser binding and, for OpaqueNoParse, runs the opaque
    parser. Full envelope assembly/handoff composition remains outside this wave.
*/
class TLogApiPublicApiFacade final {
public:
    [[nodiscard]] static TLogApiPublicCallResult AcceptOpaque(
        const TLogApiPublicCallRequest& request
    ) {
        using namespace assembler::log_level_api::content_parser;

        TLogApiPublicCallResult result{};

        if (!request.IsReady()) {
            result.status = TLogApiPublicCallStatus::Rejected;
            result.issues.push_back({
                "LOGAPI_PUBLIC_CALL_NOT_READY",
                "Public API request requires content-only input and resolved context.",
                TLogApiPublicIssueSeverity::Error,
                true
            });
            return result;
        }

        TLogApiContentParseRequest parse_request{};
        parse_request.content = request.ContentRef();
        parse_request.parser_binding = request.context.parser_binding;

        if (request.context.parser_binding->profile.IsOpaqueNoParse()) {
            result.parse_result = TLogApiOpaqueContentParser::Parse(parse_request);
            result.status = result.parse_result.IsAccepted()
                ? TLogApiPublicCallStatus::Accepted
                : TLogApiPublicCallStatus::Rejected;
            return result;
        }

        result.status = TLogApiPublicCallStatus::Rejected;
        result.issues.push_back({
            "LOGAPI_PUBLIC_CALL_UNSUPPORTED_PARSER_FOR_SKELETON",
            "This public API skeleton only executes OpaqueNoParse; specialized parsers are bound in their own packages.",
            TLogApiPublicIssueSeverity::Error,
            true
        });
        return result;
    }
};

} // namespace assembler::log_level_api::public_api

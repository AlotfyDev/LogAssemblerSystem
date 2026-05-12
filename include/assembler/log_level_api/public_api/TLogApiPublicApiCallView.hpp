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

#include <string>

#include "TLogApiPublicCallRequest.hpp"
#include "TLogApiPublicCallResult.hpp"

namespace assembler::log_level_api::public_api {

struct TLogApiPublicApiCallView final {
    std::string call_id{};
    std::string input_kind{};
    std::string content_profile_name{};
    std::string parser_name{};
    bool request_ready{false};
    bool accepted{false};

    [[nodiscard]] static TLogApiPublicApiCallView From(
        const TLogApiPublicCallRequest& request,
        const TLogApiPublicCallResult& result
    ) {
        TLogApiPublicApiCallView view{};
        view.call_id = request.id.ToString();
        view.request_ready = request.IsReady();
        view.accepted = result.IsAccepted();

        if (request.context.active_profile != nullptr) {
            view.content_profile_name = request.context.active_profile->content_profile_name;
        }
        if (request.context.parser_binding != nullptr) {
            view.parser_name = request.context.parser_binding->profile.parser_name;
        }

        switch (request.input_kind) {
            case TLogApiPublicInputKind::OpaquePayload: view.input_kind = "opaque_payload"; break;
            case TLogApiPublicInputKind::JsonText: view.input_kind = "json_text"; break;
            case TLogApiPublicInputKind::CStyleStructPrimitiveBuffer: view.input_kind = "c_style_struct_primitive_buffer"; break;
            default: view.input_kind = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::public_api

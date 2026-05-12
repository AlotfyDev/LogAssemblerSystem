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
#include "TLogApiPublicCallId.hpp"
#include "TLogApiPublicInputKind.hpp"
#include "TLogApiPublicResolvedContext.hpp"

namespace assembler::log_level_api::public_api {

/*
    Public API call request.

    Only content input is provided per call. All configuration must be resolved
    in the context beforehand.
*/
struct TLogApiPublicCallRequest final {
    TLogApiPublicCallId id{};
    TLogApiPublicInputKind input_kind{TLogApiPublicInputKind::Unknown};
    TLogApiPublicResolvedContext context{};

    TLogApiOpaquePayloadRef opaque{};
    TLogApiJsonTextRef json{};
    TLogApiCStructPayloadRef cstruct{};

    [[nodiscard]] bool HasContent() const noexcept {
        switch (input_kind) {
            case TLogApiPublicInputKind::OpaquePayload: return opaque.IsPresent();
            case TLogApiPublicInputKind::JsonText: return json.IsPresent();
            case TLogApiPublicInputKind::CStyleStructPrimitiveBuffer: return cstruct.IsPresent();
            default: return false;
        }
    }

    [[nodiscard]] assembler::log_level_api::content::TLogApiContentInputRef ContentRef() const noexcept {
        switch (input_kind) {
            case TLogApiPublicInputKind::OpaquePayload: return opaque.content;
            case TLogApiPublicInputKind::JsonText: return json.content;
            case TLogApiPublicInputKind::CStyleStructPrimitiveBuffer: return cstruct.content;
            default: return {};
        }
    }

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && input_kind != TLogApiPublicInputKind::Unknown
            && context.IsReady()
            && HasContent();
    }
};

} // namespace assembler::log_level_api::public_api

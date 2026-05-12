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

#include <vector>

#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffResult.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"
#include "TLogApiPublicCallStatus.hpp"
#include "TLogApiPublicIssue.hpp"

namespace assembler::log_level_api::public_api {

struct TLogApiPublicCallResult final {
    TLogApiPublicCallStatus status{TLogApiPublicCallStatus::Unknown};
    assembler::log_level_api::content_parser::TLogApiContentParseResult parse_result{};
    assembler::log_level_api::communication_bindings::circulation_handoff::TLogApiCirculationHandoffResult handoff_result{};
    std::vector<TLogApiPublicIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (parse_result.HasBlockingIssue()) return true;
        if (handoff_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return (status == TLogApiPublicCallStatus::Accepted
            || status == TLogApiPublicCallStatus::HandoffAccepted)
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::public_api

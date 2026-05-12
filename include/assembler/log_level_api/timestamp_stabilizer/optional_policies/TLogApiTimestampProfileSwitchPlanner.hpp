#pragma once

/*
    LOGAPI-W22 — Timestamp Stabilization Policies Optional

    Responsibility:
        Define optional policy-sensitive timestamp stabilization descriptors,
        timestamp stabilization rule profiles, change/switch requests, readiness
        reports, and policy-reference carriers.

    Boundary:
        This wave does not implement ecosystem governance, policy assignment,
        TPolicyObjectHost, realizer behavior, clock acquisition, calendar conversion,
        envelope assembly, circulation handoff, or persistence.

    Doctrine:
        Timestamp stabilization can run as configuration.
        Changing timestamp semantics may be policy-sensitive.
        This wave only models optional governance hooks for timestamp profiles.
*/

#include "TLogApiTimestampProfileSwitchRequest.hpp"
#include "TLogApiTimestampProfileSwitchResult.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

class TLogApiTimestampProfileSwitchPlanner final {
public:
    [[nodiscard]] static TLogApiTimestampProfileSwitchResult Plan(
        const TLogApiTimestampProfileSwitchRequest& request
    ) {
        TLogApiTimestampProfileSwitchResult result{};

        if (!request.IsReady()) {
            result.decision.allowed = false;
            result.decision.reason = "Timestamp profile switch request is not ready.";
            result.effective_rule = request.current_rule;
            return result;
        }

        result.decision.allowed = true;
        result.decision.reason = "Timestamp profile switch is allowed by optional readiness model.";
        result.effective_rule = request.target_rule;
        result.notes.push_back("This is readiness modeling only; no policy assignment or live mutation is performed.");
        return result;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies

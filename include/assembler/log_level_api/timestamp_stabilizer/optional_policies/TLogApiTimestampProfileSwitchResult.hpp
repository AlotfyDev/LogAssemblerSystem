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

#include <vector>

#include "TLogApiTimestampProfileSwitchDecision.hpp"
#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

struct TLogApiTimestampProfileSwitchResult final {
    TLogApiTimestampProfileSwitchDecision decision{};
    TLogApiTimestampStabilizationRuleDescriptor effective_rule{};
    std::vector<std::string> notes{};

    [[nodiscard]] bool IsAccepted() const noexcept {
        return decision.IsAllowed() && effective_rule.IsDeclared();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies

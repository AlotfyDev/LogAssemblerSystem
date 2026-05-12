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

#include <string>

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

struct TLogApiTimestampPolicyReadinessIssue final {
    std::string code{};
    std::string message{};
    bool blocking{false};

    [[nodiscard]] bool HasIssue() const noexcept {
        return !code.empty() || !message.empty();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies

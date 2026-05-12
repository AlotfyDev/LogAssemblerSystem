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

/*
    Lightweight external policy reference.

    This is not a policy object and not a policy assignment. It is only a stable
    reference slot for future governance integration.
*/
struct TLogApiTimestampPolicyRef final {
    std::string policy_id{};
    std::string policy_family{};
    std::string policy_version{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return !policy_id.empty() && !policy_family.empty() && !policy_version.empty();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies

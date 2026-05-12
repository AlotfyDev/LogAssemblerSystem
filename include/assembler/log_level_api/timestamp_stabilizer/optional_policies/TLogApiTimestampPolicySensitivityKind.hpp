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

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

enum class TLogApiTimestampPolicySensitivityKind {
    Unknown = 0,
    ConfigurationOnly,
    PolicySensitive,
    RequiresSafePoint
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies

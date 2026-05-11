#pragma once

/*
    LOGAPI-W01 — Configuration Surface And Default Profile

    This header belongs to the Log Level API configuration surface.

    Responsibility:
        Provide configuration-time types that allow Log Level API to be prepared
        before the consuming hot path receives content.

    Boundary:
        This file must not define concrete content schemas, concrete validators,
        metadata field implementation, timestamp stabilization algorithms,
        envelope assembly behavior, circulation handoff, or policy assignment.

    Doctrine:
        Configure first. Consume content only.
        The hot path uses an already resolved active profile.
*/

namespace assembler::log_level_api::api_configurator {

enum class TLogApiConfigurationStatus {
    Unknown = 0,
    Draft,
    Defaulted,
    Patched,
    Resolved,
    Active,
    Rejected
};

} // namespace assembler::log_level_api::api_configurator

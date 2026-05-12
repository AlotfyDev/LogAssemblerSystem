#pragma once

/*
    LOGAPI-W19 — Metadata Profile Registry And Update Model

    Responsibility:
        Define production-hardening metadata profile registry, metadata profile
        identity, update model, profile lookup, update admission, and registry
        view/result carriers.

    Boundary:
        Metadata remains configuration/update concern, not policy.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Metadata values may be updated through configured profile/update surfaces.
        Envelope assembly later composes content + metadata + stabilized timestamp.
*/

namespace assembler::log_level_api::metadata_injector::profile_registry {

enum class TLogApiMetadataProfileStatus {
    Unknown = 0,
    Draft,
    Registered,
    Active,
    Suspended,
    Rejected
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry

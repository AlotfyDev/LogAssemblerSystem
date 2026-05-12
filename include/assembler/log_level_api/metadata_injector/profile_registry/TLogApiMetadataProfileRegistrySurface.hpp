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

#include "TLogApiDefaultMetadataProfileRegistry.hpp"
#include "TLogApiMetadataProfileDescriptor.hpp"
#include "TLogApiMetadataProfileId.hpp"
#include "TLogApiMetadataProfileLookupKey.hpp"
#include "TLogApiMetadataProfileLookupResult.hpp"
#include "TLogApiMetadataProfileRegistry.hpp"
#include "TLogApiMetadataProfileRegistryView.hpp"
#include "TLogApiMetadataProfileStatus.hpp"
#include "TLogApiMetadataProfileUpdate.hpp"
#include "TLogApiMetadataProfileUpdateIssue.hpp"
#include "TLogApiMetadataProfileUpdateKind.hpp"
#include "TLogApiMetadataProfileUpdateResult.hpp"
#include "TLogApiMetadataProfileUpdateSet.hpp"
#include "TLogApiMetadataProfileUpdater.hpp"

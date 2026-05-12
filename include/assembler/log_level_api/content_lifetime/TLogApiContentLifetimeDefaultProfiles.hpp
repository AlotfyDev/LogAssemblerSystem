#pragma once

/*
    LOGAPI-EXT-W03 — Content Ref Lifetime And Ownership Model

    Responsibility:
        Define ownership and lifetime descriptors for Log Level API content refs,
        parsed content refs, and content container/batch refs.

    Boundary:
        This wave does not implement an allocator, memory pool, persistence,
        copying engine, security validation, circulation storage, or receiver
        lifecycle. It models lifetime/ownership contracts only.

    Doctrine:
        Non-owning content references must be accompanied by explicit lifetime
        contracts. Stable production flow must know whether payload material is
        borrowed, owned, externally owned, or stable for handoff.
*/

#include "TLogApiContentRefLease.hpp"

namespace assembler::log_level_api::content_lifetime {

struct TLogApiContentLifetimeDefaultProfiles final {
    [[nodiscard]] static TLogApiContentRefLifetimeDescriptor BorrowedDuringCall() {
        return {
            TLogApiContentRefLifetimeId{1},
            TLogApiContentRefOwnershipKind::Borrowed,
            TLogApiContentRefLifetimeKind::DuringCallOnly,
            TLogApiContentRefStabilityKind::ImmutableView,
            "borrowed_during_call"
        };
    }

    [[nodiscard]] static TLogApiContentRefLifetimeDescriptor StableUntilHandoff() {
        return {
            TLogApiContentRefLifetimeId{2},
            TLogApiContentRefOwnershipKind::ExternalStable,
            TLogApiContentRefLifetimeKind::UntilHandoffContract,
            TLogApiContentRefStabilityKind::StableForHandoff,
            "stable_until_handoff"
        };
    }

    [[nodiscard]] static TLogApiContentRefLifetimeDescriptor StableSnapshot() {
        return {
            TLogApiContentRefLifetimeId{3},
            TLogApiContentRefOwnershipKind::CopiedSnapshot,
            TLogApiContentRefLifetimeKind::StableSnapshot,
            TLogApiContentRefStabilityKind::StableForHandoff,
            "stable_snapshot"
        };
    }

    [[nodiscard]] static TLogApiContentRefLease ActiveLease(std::uint64_t id, const TLogApiContentRefLifetimeDescriptor& descriptor) {
        return {
            TLogApiContentRefLeaseId{id},
            TLogApiContentRefLeaseStatus::Active,
            descriptor
        };
    }
};

} // namespace assembler::log_level_api::content_lifetime

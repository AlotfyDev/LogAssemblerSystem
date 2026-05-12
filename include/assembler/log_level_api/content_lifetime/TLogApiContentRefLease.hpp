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

#include "TLogApiContentRefLeaseId.hpp"
#include "TLogApiContentRefLeaseStatus.hpp"
#include "TLogApiContentRefLifetimeDescriptor.hpp"

namespace assembler::log_level_api::content_lifetime {

/*
    Lease for content reference lifetime.

    This is a contract descriptor, not a memory manager.
*/
struct TLogApiContentRefLease final {
    TLogApiContentRefLeaseId id{};
    TLogApiContentRefLeaseStatus status{TLogApiContentRefLeaseStatus::Unknown};
    TLogApiContentRefLifetimeDescriptor lifetime{};

    [[nodiscard]] bool IsActive() const noexcept {
        return id.IsValid()
            && status == TLogApiContentRefLeaseStatus::Active
            && lifetime.IsDeclared();
    }

    [[nodiscard]] bool AllowsHandoff() const noexcept {
        return IsActive() && lifetime.IsSafeForHandoff();
    }
};

} // namespace assembler::log_level_api::content_lifetime

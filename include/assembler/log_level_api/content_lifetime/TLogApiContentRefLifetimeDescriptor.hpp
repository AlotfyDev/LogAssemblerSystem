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

#include <string>

#include "TLogApiContentRefLifetimeId.hpp"
#include "TLogApiContentRefLifetimeKind.hpp"
#include "TLogApiContentRefOwnershipKind.hpp"
#include "TLogApiContentRefStabilityKind.hpp"

namespace assembler::log_level_api::content_lifetime {

struct TLogApiContentRefLifetimeDescriptor final {
    TLogApiContentRefLifetimeId id{};
    TLogApiContentRefOwnershipKind ownership{TLogApiContentRefOwnershipKind::Unknown};
    TLogApiContentRefLifetimeKind lifetime{TLogApiContentRefLifetimeKind::Unknown};
    TLogApiContentRefStabilityKind stability{TLogApiContentRefStabilityKind::Unknown};

    std::string label{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && ownership != TLogApiContentRefOwnershipKind::Unknown
            && lifetime != TLogApiContentRefLifetimeKind::Unknown
            && stability != TLogApiContentRefStabilityKind::Unknown
            && !label.empty();
    }

    [[nodiscard]] bool IsSafeForHandoff() const noexcept {
        return IsDeclared()
            && (stability == TLogApiContentRefStabilityKind::StableForHandoff
                || stability == TLogApiContentRefStabilityKind::ImmutableView)
            && (lifetime == TLogApiContentRefLifetimeKind::UntilHandoffContract
                || lifetime == TLogApiContentRefLifetimeKind::UntilCirculationClaim
                || lifetime == TLogApiContentRefLifetimeKind::StableSnapshot
                || lifetime == TLogApiContentRefLifetimeKind::ExternalManaged);
    }
};

} // namespace assembler::log_level_api::content_lifetime

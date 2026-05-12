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

#include "TLogApiContentRefLease.hpp"

namespace assembler::log_level_api::content_lifetime {

struct TLogApiContentLifetimeView final {
    std::string lease_id{};
    std::string label{};
    bool active{false};
    bool safe_for_handoff{false};

    [[nodiscard]] static TLogApiContentLifetimeView From(const TLogApiContentRefLease& lease) {
        TLogApiContentLifetimeView view{};
        view.lease_id = lease.id.ToString();
        view.label = lease.lifetime.label;
        view.active = lease.IsActive();
        view.safe_for_handoff = lease.AllowsHandoff();
        return view;
    }
};

} // namespace assembler::log_level_api::content_lifetime

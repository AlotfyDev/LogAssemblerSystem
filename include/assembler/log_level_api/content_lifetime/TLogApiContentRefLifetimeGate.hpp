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
#include "TLogApiContentRefLifetimeReport.hpp"

namespace assembler::log_level_api::content_lifetime {

class TLogApiContentRefLifetimeGate final {
public:
    [[nodiscard]] static TLogApiContentRefLifetimeReport Evaluate(const TLogApiContentRefLease& lease) {
        TLogApiContentRefLifetimeReport report{};
        report.lease = lease;

        if (!lease.IsActive()) {
            report.issues.push_back({
                "LOGAPI_CONTENT_REF_LEASE_NOT_ACTIVE",
                "Content reference lease must be active.",
                true
            });
            return report;
        }

        if (!lease.lifetime.IsDeclared()) {
            report.issues.push_back({
                "LOGAPI_CONTENT_REF_LIFETIME_NOT_DECLARED",
                "Content reference lifetime descriptor must be declared.",
                true
            });
        }

        return report;
    }

    [[nodiscard]] static bool AllowsHandoff(const TLogApiContentRefLease& lease) noexcept {
        return lease.AllowsHandoff();
    }
};

} // namespace assembler::log_level_api::content_lifetime

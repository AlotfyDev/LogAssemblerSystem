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

namespace assembler::log_level_api::content_lifetime {

enum class TLogApiContentRefOwnershipKind {
    Unknown = 0,
    Borrowed,
    OwnedByLogApi,
    OwnedByCaller,
    ExternalStable,
    CopiedSnapshot
};

} // namespace assembler::log_level_api::content_lifetime

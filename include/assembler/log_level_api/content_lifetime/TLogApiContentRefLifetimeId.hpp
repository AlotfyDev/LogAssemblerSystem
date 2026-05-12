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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content_lifetime {

struct TLogApiContentRefLifetimeId final {
    std::uint64_t value{0};

    constexpr TLogApiContentRefLifetimeId() = default;
    constexpr explicit TLogApiContentRefLifetimeId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-content-ref-lifetime-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::content_lifetime

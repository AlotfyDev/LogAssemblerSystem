#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TIngressState : std::uint8_t { uninitialized, ready, awaiting_ref, placing, placed, blocked_by_invariant, closed };
[[nodiscard]] constexpr bool ingress_ready(TIngressState s) noexcept { return s == TIngressState::ready || s == TIngressState::awaiting_ref; }
} // namespace circulation_mechanism
} // namespace assembler

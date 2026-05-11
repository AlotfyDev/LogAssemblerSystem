#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TSafePointState : std::uint8_t { unavailable, pending, available, claimed, consumed, expired, violated };
[[nodiscard]] constexpr bool can_claim(TSafePointState s) noexcept { return s == TSafePointState::available; }
} // namespace circulation_mechanism
} // namespace assembler

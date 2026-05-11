#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TReferenceValidityState : std::uint8_t { prepared, issued, consumed, expired, invalidated, stale_detected, blocked_by_state };
[[nodiscard]] constexpr bool is_usable(TReferenceValidityState s) noexcept { return s == TReferenceValidityState::issued; }
} // namespace circulation_mechanism
} // namespace assembler

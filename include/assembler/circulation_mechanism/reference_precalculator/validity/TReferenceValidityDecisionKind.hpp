#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TReferenceValidityDecisionKind : std::uint8_t { valid, expired, invalidated, blocked_by_state, stale_detected, direction_mismatch, generation_mismatch, invalid_scope };
} // namespace circulation_mechanism
} // namespace assembler

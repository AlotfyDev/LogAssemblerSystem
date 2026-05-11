#pragma once
#include "TReferenceValidityDecisionKind.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TAccessRefDirection.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceValidityPolicy final {
    [[nodiscard]] static constexpr TReferenceValidityDecisionKind decide(TReferenceValidityState state, TAccessRefDirection expected, TAccessRefDirection observed) noexcept {
        if (expected != observed) return TReferenceValidityDecisionKind::direction_mismatch;
        if (state == TReferenceValidityState::issued) return TReferenceValidityDecisionKind::valid;
        if (state == TReferenceValidityState::expired) return TReferenceValidityDecisionKind::expired;
        if (state == TReferenceValidityState::invalidated) return TReferenceValidityDecisionKind::invalidated;
        if (state == TReferenceValidityState::stale_detected) return TReferenceValidityDecisionKind::stale_detected;
        if (state == TReferenceValidityState::blocked_by_state) return TReferenceValidityDecisionKind::blocked_by_state;
        return TReferenceValidityDecisionKind::invalid_scope;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

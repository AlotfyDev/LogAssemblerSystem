#pragma once
#include "TReferenceValidityDecisionKind.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TAccessRefId.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TStaleReferenceReport final {
    TAccessRefId reference_id{};
    TReferenceValidityState observed_state{TReferenceValidityState::stale_detected};
    TReferenceValidityDecisionKind decision{TReferenceValidityDecisionKind::stale_detected};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return reference_id.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

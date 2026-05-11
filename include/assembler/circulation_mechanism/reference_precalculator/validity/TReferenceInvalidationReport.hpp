#pragma once
#include "assembler/circulation_mechanism/reference_precalculator/handles/TAccessRefId.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceInvalidationReport final {
    TAccessRefId reference_id{};
    TReferenceValidityState before{TReferenceValidityState::issued};
    TReferenceValidityState after{TReferenceValidityState::invalidated};
    bool accepted{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return reference_id.is_valid(); }
    [[nodiscard]] constexpr bool invalidated() const noexcept { return accepted && after == TReferenceValidityState::invalidated; }
};
} // namespace circulation_mechanism
} // namespace assembler

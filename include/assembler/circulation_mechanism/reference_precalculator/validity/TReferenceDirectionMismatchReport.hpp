#pragma once
#include "TReferenceValidityDecisionKind.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TAccessRefId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TAccessRefDirection.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceDirectionMismatchReport final {
    TAccessRefId reference_id{};
    TAccessRefDirection expected{TAccessRefDirection::ingress};
    TAccessRefDirection observed{TAccessRefDirection::dispatch};
    TReferenceValidityDecisionKind decision{TReferenceValidityDecisionKind::direction_mismatch};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return reference_id.is_valid() && expected != observed; }
};
} // namespace circulation_mechanism
} // namespace assembler

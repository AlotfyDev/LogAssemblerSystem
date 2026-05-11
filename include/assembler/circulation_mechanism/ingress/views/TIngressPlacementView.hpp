#pragma once
#include "assembler/circulation_mechanism/ingress/TIngressPayloadEnvelopeRef.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TIngressAccessRef.hpp"
#include "assembler/circulation_mechanism/ingress/TIngressPlacementStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressPlacementView final {
    TIngressPayloadEnvelopeRef payload{};
    TIngressAccessRef ref{};
    TIngressPlacementStatus status{TIngressPlacementStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return payload.is_valid() && ref.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TIngressPlacementStatus::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

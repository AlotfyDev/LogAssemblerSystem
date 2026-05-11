#pragma once
#include "assembler/circulation_mechanism/ingress/TIngressPayloadEnvelopeRef.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TIngressAccessRef.hpp"
#include "assembler/circulation_mechanism/ingress/boundary/TIngressBoundaryDescriptor.hpp"
#include "assembler/circulation_mechanism/ingress/TIngressPlacementStatus.hpp"

/*
    TIngressAccessPolicy.hpp
    Validates whether placement may be attempted. Does not mutate target.
*/
namespace assembler {
namespace circulation_mechanism {

struct TIngressAccessPolicy final {
    [[nodiscard]] static constexpr TIngressPlacementStatus validate(TIngressPayloadEnvelopeRef payload, TIngressAccessRef ref, TIngressBoundaryDescriptor boundary) noexcept {
        if (!boundary.is_valid() || !boundary.ready() || !boundary.boundary_safe()) return TIngressPlacementStatus::rejected_boundary_mismatch;
        if (!payload.is_valid()) return TIngressPlacementStatus::rejected_payload_not_ready;
        if (!ref.base.id.is_valid() || !ref.base.scope.is_valid()) return TIngressPlacementStatus::rejected_invalid_ref;
        if (ref.base.direction != TAccessRefDirection::ingress || ref.base.kind != TAccessRefKind::ingress_access) return TIngressPlacementStatus::rejected_wrong_ref_direction;
        if (!ref.base.can_be_consumed()) return TIngressPlacementStatus::rejected_invalid_ref;
        return TIngressPlacementStatus::accepted;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

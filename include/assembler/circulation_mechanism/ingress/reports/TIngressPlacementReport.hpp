#pragma once
#include "TIngressReportId.hpp"
#include "assembler/circulation_mechanism/ingress/TIngressPayloadEnvelopeRef.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TIngressAccessRef.hpp"
#include "assembler/circulation_mechanism/ingress/TIngressPlacementStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressPlacementReport final {
    TIngressReportId report_id{};
    TIngressPayloadEnvelopeRef payload{};
    TIngressAccessRef ref{};
    TIngressPlacementStatus status{TIngressPlacementStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TIngressPlacementStatus::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "TReferenceReportId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculatorId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculationStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceSupplyInterruptionReport final {
    TReferenceReportId report_id{};
    TReferencePrecalculatorId precalculator_id{};
    TReferencePrecalculationStatus observed_status{TReferencePrecalculationStatus::supply_interrupted};
    bool continuous_supply_required{true};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && precalculator_id.is_valid(); }
    [[nodiscard]] constexpr bool is_violation() const noexcept { return continuous_supply_required && observed_status == TReferencePrecalculationStatus::supply_interrupted; }
};
} // namespace circulation_mechanism
} // namespace assembler

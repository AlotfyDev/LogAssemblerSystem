#pragma once
#include "TReferenceReportId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculatorId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculationStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferencePrecalculationReport final {
    TReferenceReportId report_id{};
    TReferencePrecalculatorId precalculator_id{};
    TReferencePrecalculationStatus status{TReferencePrecalculationStatus::uninitialized};
    std::uint32_t ingress_refs_prepared{0};
    std::uint32_t dispatch_refs_prepared{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && precalculator_id.is_valid(); }
    [[nodiscard]] constexpr bool prepared_any() const noexcept { return ingress_refs_prepared > 0U || dispatch_refs_prepared > 0U; }
};
} // namespace circulation_mechanism
} // namespace assembler

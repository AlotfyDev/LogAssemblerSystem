#pragma once
#include <cstdint>
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculatorId.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculationStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceSupplyView final {
    TReferencePrecalculatorId precalculator_id{};
    TReferencePrecalculationStatus status{TReferencePrecalculationStatus::uninitialized};
    std::uint32_t ingress_refs_ready{0};
    std::uint32_t dispatch_refs_ready{0};
    bool supply_interrupted{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return precalculator_id.is_valid(); }
    [[nodiscard]] constexpr bool has_ingress_refs() const noexcept { return ingress_refs_ready > 0U; }
    [[nodiscard]] constexpr bool has_dispatch_refs() const noexcept { return dispatch_refs_ready > 0U; }
};
} // namespace circulation_mechanism
} // namespace assembler

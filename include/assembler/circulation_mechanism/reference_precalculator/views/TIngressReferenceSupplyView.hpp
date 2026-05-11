#pragma once
#include "TReferenceSupplyView.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressReferenceSupplyView final {
    TReferenceSupplyView base{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return base.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return base.has_ingress_refs() && !base.supply_interrupted; }
};
} // namespace circulation_mechanism
} // namespace assembler

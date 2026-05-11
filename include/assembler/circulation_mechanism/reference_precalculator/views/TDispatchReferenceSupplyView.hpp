#pragma once
#include "TReferenceSupplyView.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchReferenceSupplyView final {
    TReferenceSupplyView base{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return base.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return base.has_dispatch_refs() && !base.supply_interrupted; }
};
} // namespace circulation_mechanism
} // namespace assembler

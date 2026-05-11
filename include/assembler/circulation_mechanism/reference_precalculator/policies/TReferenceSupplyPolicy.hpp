#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

struct TReferenceSupplyPolicy final {
    std::uint32_t ingress_supply_depth{0};
    std::uint32_t dispatch_supply_depth{0};
    bool continuous_supply_required{true};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return ingress_supply_depth > 0U && dispatch_supply_depth > 0U; }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "assembler/circulation_mechanism/reference_precalculator/policies/TReferenceSupplyPolicy.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeReferenceSupplyBinding final {
    TReferenceSupplyPolicy supply_policy{};
    bool continuous_supply_required{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return supply_policy.is_valid()
            && (!continuous_supply_required || supply_policy.continuous_supply_required);
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

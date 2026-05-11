#pragma once
#include "assembler/circulation_mechanism/capacity/TCirculationCapacityProfile.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeCapacityBinding final {
    TCirculationCapacityProfile capacity_profile{};
    bool extreme_default_expected{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return capacity_profile.is_valid()
            && (!extreme_default_expected || capacity_profile.extreme_default_enabled);
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

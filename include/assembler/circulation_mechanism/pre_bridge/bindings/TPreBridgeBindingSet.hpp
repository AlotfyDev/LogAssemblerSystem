#pragma once
#include "TPreBridgeBindingSetId.hpp"
#include "TPreBridgeCapacityBinding.hpp"
#include "TPreBridgeBoundaryBinding.hpp"
#include "TPreBridgeReferenceSupplyBinding.hpp"
#include "TPreBridgeDiagnosticsBinding.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeBindingSet final {
    TPreBridgeBindingSetId binding_set_id{};
    TPreBridgeCapacityBinding capacity{};
    TPreBridgeBoundaryBinding boundary{};
    TPreBridgeReferenceSupplyBinding reference_supply{};
    TPreBridgeDiagnosticsBinding diagnostics{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return binding_set_id.is_valid()
            && capacity.is_valid()
            && boundary.is_valid()
            && reference_supply.is_valid()
            && diagnostics.is_valid();
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "../TPreBridgeEngineId.hpp"
#include "../runtime/TPreBridgeRuntimeState.hpp"
#include "assembler/circulation_mechanism/runtime_core/views/TCirculationRuntimeView.hpp"

/*
    TPreBridgeEngineView.hpp

    Current responsibility:
        Read-only projection of PreBridge engine readiness and runtime state.
*/
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeEngineView final {
    TPreBridgeEngineId engine_id{};
    TPreBridgeRuntimeState state{TPreBridgeRuntimeState::unconfigured};
    TCirculationRuntimeView shared_runtime{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return engine_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept {
        return is_valid() && (state == TPreBridgeRuntimeState::ready || state == TPreBridgeRuntimeState::running);
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "../TReadSideEngineId.hpp"
#include "../runtime/TReadSideRuntimeState.hpp"
#include "assembler/circulation_mechanism/runtime_core/views/TCirculationRuntimeView.hpp"

/*
    TReadSideEngineView.hpp

    Current responsibility:
        Read-only projection of ReadSide engine readiness and runtime state.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideEngineView final {
    TReadSideEngineId engine_id{};
    TReadSideRuntimeState state{TReadSideRuntimeState::unconfigured};
    TCirculationRuntimeView shared_runtime{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return engine_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept {
        return is_valid() && (state == TReadSideRuntimeState::ready || state == TReadSideRuntimeState::running);
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "TCirculationLifecycleStatus.hpp"
#include "../reports/TCirculationRuntimeIssueKind.hpp"

/*
    TCirculationLifecycleTransition.hpp

    Responsibility:
        Shared lifecycle transition contract for PreBridge and ReadSide facades.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationLifecycleTransitionResult final {
    bool accepted{false};
    TCirculationRuntimeIssueKind issue{TCirculationRuntimeIssueKind::none};
    TCirculationLifecycleStatus before{TCirculationLifecycleStatus::unconfigured};
    TCirculationLifecycleStatus after{TCirculationLifecycleStatus::unconfigured};
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted; }
};

[[nodiscard]] constexpr bool can_transition(TCirculationLifecycleStatus from, TCirculationLifecycleStatus to) noexcept {
    if (from == to) return true;
    switch (from) {
        case TCirculationLifecycleStatus::unconfigured: return to == TCirculationLifecycleStatus::configured || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::configured: return to == TCirculationLifecycleStatus::constructed || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::constructed: return to == TCirculationLifecycleStatus::initialized || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::initialized: return to == TCirculationLifecycleStatus::running || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::running: return to == TCirculationLifecycleStatus::draining || to == TCirculationLifecycleStatus::releasing || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::draining: return to == TCirculationLifecycleStatus::releasing || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::releasing: return to == TCirculationLifecycleStatus::recycling || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::recycling: return to == TCirculationLifecycleStatus::initialized || to == TCirculationLifecycleStatus::stopped || to == TCirculationLifecycleStatus::faulted;
        case TCirculationLifecycleStatus::stopped: return to == TCirculationLifecycleStatus::configured;
        case TCirculationLifecycleStatus::faulted: return to == TCirculationLifecycleStatus::stopped;
        default: return false;
    }
}

[[nodiscard]] constexpr TCirculationLifecycleTransitionResult validate_transition(TCirculationLifecycleStatus from, TCirculationLifecycleStatus to) noexcept {
    return can_transition(from, to)
        ? TCirculationLifecycleTransitionResult{true, TCirculationRuntimeIssueKind::none, from, to}
        : TCirculationLifecycleTransitionResult{false, TCirculationRuntimeIssueKind::invalid_lifecycle_transition, from, to};
}
} // namespace circulation_mechanism
} // namespace assembler

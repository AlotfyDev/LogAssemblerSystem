#pragma once
#include "TCirculationRuntimeId.hpp"
#include "configuration/TCirculationConfigurationDescriptor.hpp"
#include "lifecycle/TCirculationLifecycleStatus.hpp"

/*
    TCirculationRuntimeDescriptor.hpp

    Responsibility:
        Shared runtime descriptor for future PreBridge/ReadSide facades.

    Non-ownership:
        Does not execute runtime or own subsystem-specific behavior.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationRuntimeDescriptor final {
    TCirculationRuntimeId runtime_id{};
    TCirculationConfigurationDescriptor configuration{};
    TCirculationLifecycleStatus lifecycle_status{TCirculationLifecycleStatus::unconfigured};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return runtime_id.is_valid();
    }

    [[nodiscard]] constexpr bool configured() const noexcept {
        return configuration.ready_for_runtime()
            && lifecycle_status != TCirculationLifecycleStatus::unconfigured
            && lifecycle_status != TCirculationLifecycleStatus::faulted;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

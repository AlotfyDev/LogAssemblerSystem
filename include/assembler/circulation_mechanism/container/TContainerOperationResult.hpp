#pragma once
#include "TContainerOperationStatus.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TContainerOperationResult final {
    TContainerOperationStatus status{TContainerOperationStatus::not_attempted};
    TContainerState before{TContainerState::default_empty};
    TContainerState after{TContainerState::default_empty};
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TContainerOperationStatus::accepted; }
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted(); }
};
} // namespace circulation_mechanism
} // namespace assembler

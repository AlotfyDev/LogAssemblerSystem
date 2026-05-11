#pragma once
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TContainerStateTransitionReport final {
    TContainerId container_id{};
    TContainerState before{TContainerState::default_empty};
    TContainerState after{TContainerState::default_empty};
    bool accepted{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return container_id.is_valid(); }
    [[nodiscard]] constexpr bool changed() const noexcept { return before != after; }
};
} // namespace circulation_mechanism
} // namespace assembler

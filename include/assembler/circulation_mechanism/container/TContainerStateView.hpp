#pragma once
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TContainerStateView final {
    TContainerId container_id{};
    TContainerState state{TContainerState::default_empty};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return container_id.is_valid(); }
    [[nodiscard]] constexpr bool ingress_eligible() const noexcept { return can_join_ingress_round(state); }
    [[nodiscard]] constexpr bool dispatch_eligible() const noexcept { return can_join_dispatch_round(state); }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TReentryEligibilityView final {
    TContainerId container_id{};
    TContainerState state{TContainerState::default_empty};
    bool reset_applied{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return container_id.is_valid(); }
    [[nodiscard]] constexpr bool eligible() const noexcept {
        return is_valid() && reset_applied && (state == TContainerState::default_empty || state == TContainerState::ingress_ready);
    }
};
} // namespace circulation_mechanism
} // namespace assembler

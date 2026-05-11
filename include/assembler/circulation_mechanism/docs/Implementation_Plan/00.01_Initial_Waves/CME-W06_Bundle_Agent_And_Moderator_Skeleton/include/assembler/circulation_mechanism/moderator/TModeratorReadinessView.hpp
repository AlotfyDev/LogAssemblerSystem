#pragma once

#include "TModeratorId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TModeratorState.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

/*
    TModeratorReadinessView.hpp

    Responsibility:
        Read-only projection of moderator readiness for one container.

    Does not own:
        - Round admission.
        - Waiting-list mutation.
        - Reference calculation.
*/

namespace assembler {
namespace circulation_mechanism {

struct TModeratorReadinessView final
{
    TModeratorId moderator_id{};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TModeratorState moderator_state{TModeratorState::idle};
    TContainerState container_state{TContainerState::default_empty};
    bool safe_point_available{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return moderator_id.is_valid()
            && container_id.is_valid()
            && registry_index.is_valid();
    }

    [[nodiscard]] constexpr bool can_expose_ingress_ready() const noexcept
    {
        return is_valid()
            && safe_point_available
            && (container_state == TContainerState::default_empty
                || container_state == TContainerState::ingress_ready);
    }
};
} // namespace circulation_mechanism
} // namespace assembler

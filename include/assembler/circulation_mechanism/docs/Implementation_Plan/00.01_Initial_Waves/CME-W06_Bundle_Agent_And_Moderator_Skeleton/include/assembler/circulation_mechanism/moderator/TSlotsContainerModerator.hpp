#pragma once

#include "TModeratorId.hpp"
#include "TSlotsContainerModeratorConfig.hpp"
#include "TModeratorReadinessView.hpp"
#include "TModeratedContainerView.hpp"
#include "TContainerResetReport.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TModeratorState.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

/*
    TSlotsContainerModerator.hpp

    Wave:
        CME-W06_Bundle_Agent_And_Moderator_Skeleton

    Responsibility:
        Defines a per-container moderator skeleton responsible for readiness and
        reset surface around one registered container.

    Owns:
        - Moderator identity.
        - The moderated container id/index relation.
        - Readiness view.
        - Reset report surface.

    Does not own:
        - Bundle topology.
        - Uniform capacity profile ownership.
        - Round membership decisions.
        - Reference calculation.
        - Dispatch exposure.
*/

namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerModerator final
{
    TModeratorId id{};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TSlotsContainerModeratorConfig config{};
    TModeratorState state{TModeratorState::idle};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return id.is_valid()
            && container_id.is_valid()
            && registry_index.is_valid()
            && config.is_valid();
    }

    [[nodiscard]] constexpr TModeratorReadinessView readiness_view(
        TContainerState container_state,
        bool safe_point_available) const noexcept
    {
        return TModeratorReadinessView{
            id,
            container_id,
            registry_index,
            state,
            container_state,
            safe_point_available
        };
    }

    [[nodiscard]] constexpr TModeratedContainerView moderated_container_view(
        TContainerState container_state,
        bool safe_point_available) const noexcept
    {
        return TModeratedContainerView{readiness_view(container_state, safe_point_available)};
    }

    [[nodiscard]] constexpr TContainerResetReport reset_report(
        TContainerState before,
        TContainerState after,
        bool accepted) const noexcept
    {
        return TContainerResetReport{id, container_id, registry_index, before, after, accepted};
    }
};
} // namespace circulation_mechanism
} // namespace assembler

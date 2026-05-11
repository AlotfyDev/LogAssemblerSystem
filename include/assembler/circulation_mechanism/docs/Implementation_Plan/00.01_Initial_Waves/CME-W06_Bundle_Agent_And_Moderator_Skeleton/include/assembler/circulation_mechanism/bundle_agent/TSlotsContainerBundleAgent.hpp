#pragma once

#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "TSlotsContainerBundleAgentConfig.hpp"
#include "TBundleTopologyView.hpp"
#include "TBundleScalingReport.hpp"
#include "TDefaultEmptyContainerProfileReport.hpp"
#include "assembler/circulation_mechanism/state/TBundleAgentState.hpp"

/*
    TSlotsContainerBundleAgent.hpp

    Wave:
        CME-W06_Bundle_Agent_And_Moderator_Skeleton

    Responsibility:
        Defines the BundleAgent skeleton as the topology and capacity profile
        owner for a family of uniform containers.

    Owns:
        - Agent identity.
        - Container family identity.
        - Capacity profile configuration.
        - Bundle agent state projection.
        - Topology views and reports.

    Does not own:
        - Concrete container reset.
        - Per-container moderation.
        - Registry mutation algorithm.
        - Waiting-list membership.
        - Reference calculation.
        - Ingress/dispatch access.
*/

namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerBundleAgent final
{
    TBundleAgentId id{};
    TContainerFamilyId family_id{};
    TSlotsContainerBundleAgentConfig config{};
    TBundleAgentState state{TBundleAgentState::stable};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return id.is_valid() && family_id.is_valid() && config.is_valid();
    }

    [[nodiscard]] constexpr TBundleTopologyView topology_view() const noexcept
    {
        return TBundleTopologyView{
            id,
            family_id,
            state,
            config.capacity_profile.container_count,
            config.capacity_profile.container_count
        };
    }

    [[nodiscard]] constexpr TDefaultEmptyContainerProfileReport default_empty_profile_report() const noexcept
    {
        return TDefaultEmptyContainerProfileReport{
            id,
            family_id,
            config.capacity_profile.profile_id,
            config.capacity_profile.is_valid()
        };
    }

    [[nodiscard]] constexpr TBundleScalingReport scaling_report(TScalingDirectionKind direction, bool accepted) const noexcept
    {
        return TBundleScalingReport{id, family_id, direction, accepted};
    }
};
} // namespace circulation_mechanism
} // namespace assembler

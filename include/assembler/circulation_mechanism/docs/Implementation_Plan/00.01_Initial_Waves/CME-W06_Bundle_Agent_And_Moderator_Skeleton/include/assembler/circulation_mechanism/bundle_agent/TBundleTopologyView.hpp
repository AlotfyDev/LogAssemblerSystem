#pragma once

#include <cstdint>
#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "assembler/circulation_mechanism/state/TBundleAgentState.hpp"

/*
    TBundleTopologyView.hpp

    Wave:
        CME-W06_Bundle_Agent_And_Moderator_Skeleton

    Responsibility:
        Read-only projection of the bundle topology owned by the BundleAgent.

    Architectural role:
        Exposes topology and capacity status without allowing mutation.

    Does not own:
        - Registry storage.
        - Container reset.
        - Scaling execution.
        - Round membership.
*/

namespace assembler {
namespace circulation_mechanism {

struct TBundleTopologyView final
{
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TBundleAgentState state{TBundleAgentState::stable};
    std::uint32_t configured_container_count{0};
    std::uint32_t active_container_count{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return bundle_agent_id.is_valid()
            && family_id.is_valid()
            && configured_container_count > 0U
            && active_container_count <= configured_container_count;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

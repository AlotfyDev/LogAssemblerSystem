#pragma once
#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "TContainerFamilyShape.hpp"
#include "assembler/circulation_mechanism/state/TBundleAgentState.hpp"

/*
    TBundleTopologyView.hpp

    Responsibility:
        Read-only projection of BundleAgent topology.

    Non-ownership:
        Does not mutate topology or registry storage.
*/
namespace assembler {
namespace circulation_mechanism {

struct TBundleTopologyView final {
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TBundleAgentState state{TBundleAgentState::uninitialized};
    TContainerFamilyShape shape{};
    std::uint32_t max_container_count{0};
    std::uint64_t generation{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return bundle_agent_id.is_valid()
            && family_id.is_valid()
            && shape.is_valid()
            && max_container_count >= shape.active_container_count
            && generation > 0U;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

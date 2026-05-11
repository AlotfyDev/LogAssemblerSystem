#pragma once

#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "assembler/circulation_mechanism/capacity/TCapacityProfileId.hpp"

/*
    TDefaultEmptyContainerProfileReport.hpp

    Responsibility:
        Reports which default empty container profile is supplied by BundleAgent.

    Does not own:
        - Applying reset to concrete containers.
        - Container storage.
*/

namespace assembler {
namespace circulation_mechanism {

struct TDefaultEmptyContainerProfileReport final
{
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TCapacityProfileId capacity_profile_id{};
    bool profile_available{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return bundle_agent_id.is_valid()
            && family_id.is_valid()
            && capacity_profile_id.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

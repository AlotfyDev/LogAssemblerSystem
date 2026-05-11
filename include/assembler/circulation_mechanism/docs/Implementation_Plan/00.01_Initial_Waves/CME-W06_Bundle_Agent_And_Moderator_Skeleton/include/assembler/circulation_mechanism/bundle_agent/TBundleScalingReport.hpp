#pragma once

#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "assembler/circulation_mechanism/capacity/TScalingDirectionKind.hpp"

/*
    TBundleScalingReport.hpp

    Responsibility:
        Records a bundle scaling planning/result event.

    Does not own:
        - Actual registry mutation.
        - Safe-point execution.
        - Per-container reset.
*/

namespace assembler {
namespace circulation_mechanism {

struct TBundleScalingReport final
{
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TScalingDirectionKind direction{TScalingDirectionKind::none};
    bool accepted{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return bundle_agent_id.is_valid() && family_id.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

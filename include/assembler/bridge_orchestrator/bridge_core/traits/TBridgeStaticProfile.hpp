#pragma once
#include <cstddef>
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocationProfile.hpp"

namespace assembler::communication_context
{
    template <std::size_t PlanCapacity>
    struct TBridgeStaticProfile final
    {
        static constexpr std::size_t plan_capacity = PlanCapacity;
        TBridgeEndpointInvocationProfile invocation_profile{TBridgeEndpointInvocationProfile::model_only_profile()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return PlanCapacity > 0u && invocation_profile.is_valid();
        }
    };
}

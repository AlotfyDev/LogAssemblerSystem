#pragma once
#include <string_view>

namespace assembler::communication_context
{
    enum class TBridgeEndpointInvocationMode
    {
        unknown,
        model_only,
        model_plus_invocation,
        diagnostic_only
    };

    struct TBridgeEndpointInvocationProfile final
    {
        TBridgeEndpointInvocationMode mode{TBridgeEndpointInvocationMode::model_only};
        bool invocation_allowed{false};
        bool collect_invocation_evidence{true};
        std::string_view profile_name{"model_only_endpoint_invocation_profile"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return mode != TBridgeEndpointInvocationMode::unknown && !profile_name.empty();
        }

        [[nodiscard]] constexpr bool model_only() const noexcept
        {
            return mode == TBridgeEndpointInvocationMode::model_only && !invocation_allowed;
        }

        [[nodiscard]] static constexpr TBridgeEndpointInvocationProfile model_only_profile() noexcept
        {
            return {TBridgeEndpointInvocationMode::model_only, false, true, "model_only_endpoint_invocation_profile"};
        }

        [[nodiscard]] static constexpr TBridgeEndpointInvocationProfile model_plus_invocation_profile() noexcept
        {
            return {TBridgeEndpointInvocationMode::model_plus_invocation, true, true, "model_plus_invocation_profile"};
        }
    };
}

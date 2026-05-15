#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

namespace assembler::communication_context
{
    enum class TBridgeEndpointInvocationStatus
    {
        unknown,
        not_attempted,
        allowed,
        blocked,
        attempted,
        succeeded,
        failed
    };

    struct TBridgeEndpointInvocation final
    {
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBridgeEndpointInvocationStatus status{TBridgeEndpointInvocationStatus::not_attempted};
        TBridgeResult result{TBridgeResult::success()};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view operation_name{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol != TBridgeProtocolKind::unknown
                && status != TBridgeEndpointInvocationStatus::unknown;
        }

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return status == TBridgeEndpointInvocationStatus::succeeded
                && result.succeeded();
        }

        [[nodiscard]] static constexpr TBridgeEndpointInvocation not_attempted(
            TBridgeProtocolKind protocol_kind,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view operation = {},
            std::string_view text = "endpoint invocation not attempted") noexcept
        {
            return {protocol_kind, TBridgeEndpointInvocationStatus::not_attempted, TBridgeResult::success(token), token, operation, text};
        }
    };
}

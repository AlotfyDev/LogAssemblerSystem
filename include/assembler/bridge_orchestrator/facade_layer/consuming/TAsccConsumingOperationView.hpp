#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentDescriptor.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccOperationMode.hpp"

namespace assembler::communication_context
{
    struct TAsccConsumingOperationView final
    {
        TAsccComponentDescriptor component{};
        TAsccComponentProfileId active_profile{TAsccComponentProfileId::invalid()};
        TBridgeId bridge_id{TBridgeId::invalid()};
        TAsccOperationMode operation_mode{TAsccOperationMode::unknown};
        bool operation_admitted{false};
        std::string_view operation_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return component.is_valid()
                && active_profile.is_valid()
                && bridge_id.is_valid()
                && operation_mode != TAsccOperationMode::unknown;
        }

        [[nodiscard]] constexpr bool can_consume() const noexcept
        {
            return is_valid() && operation_admitted;
        }
    };
}

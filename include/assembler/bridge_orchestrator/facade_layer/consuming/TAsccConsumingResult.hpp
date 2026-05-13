#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccOperationMode.hpp"

namespace assembler::communication_context
{
    struct TAsccConsumingResult final
    {
        TAsccOperationMode operation_mode{TAsccOperationMode::unknown};
        TBridgeCoreResult bridge_result{};
        bool invocation_attempted{false};
        bool evidence_available{false};
        std::string_view result_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return operation_mode != TAsccOperationMode::unknown;
        }

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return is_valid() && bridge_result.succeeded();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_valid() && bridge_result.failed();
        }
    };
}

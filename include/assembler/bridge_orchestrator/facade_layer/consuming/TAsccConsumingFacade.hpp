#pragma once

#include "assembler/communication_context/facade_layer/consuming/TAsccConsumingOperationView.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccConsumingResult.hpp"

namespace assembler::communication_context
{
    struct TAsccConsumingFacade final
    {
        TAsccConsumingOperationView operation_view{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return operation_view.is_valid();
        }

        [[nodiscard]] constexpr bool can_consume() const noexcept
        {
            return operation_view.can_consume();
        }

        [[nodiscard]] static constexpr TAsccConsumingResult rejected(
            TAsccOperationMode mode,
            std::string_view note = "ASCC consuming operation is not admitted") noexcept
        {
            return TAsccConsumingResult{
                mode,
                TBridgeCoreResult{},
                false,
                true,
                note
            };
        }
    };
}

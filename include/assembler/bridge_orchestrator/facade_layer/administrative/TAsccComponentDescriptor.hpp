#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/common/TAsccComponentId.hpp"
#include "assembler/communication_context/facade_layer/common/TAsccComponentVersion.hpp"

namespace assembler::communication_context
{
    struct TAsccComponentDescriptor final
    {
        TAsccComponentId component_id{TAsccComponentId::invalid()};
        TAsccComponentVersion version{};
        std::string_view component_name{};
        std::string_view namespace_name{"assembler::communication_context"};
        std::string_view component_role{"communication_context"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return component_id.is_valid()
                && version.is_valid()
                && !component_name.empty();
        }

        [[nodiscard]] static constexpr TAsccComponentDescriptor communication_context_v1(
            TAsccComponentId id,
            std::string_view name = "ASCC Communication Context") noexcept
        {
            return TAsccComponentDescriptor{
                id,
                TAsccComponentVersion::v1(),
                name,
                "assembler::communication_context",
                "communication_context"
            };
        }
    };
}

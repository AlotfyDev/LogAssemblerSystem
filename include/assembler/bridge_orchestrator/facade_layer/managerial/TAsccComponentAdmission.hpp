#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/administrative/TAsccComponentDescriptor.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"

namespace assembler::communication_context
{
    struct TAsccComponentAdmission final
    {
        TAsccComponentDescriptor component{};
        TAsccComponentProfileId selected_profile{TAsccComponentProfileId::invalid()};
        bool configuration_valid{false};
        bool capabilities_satisfied{false};
        bool protocol_requirements_satisfied{false};
        bool binding_requirements_satisfied{false};
        std::string_view admission_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return component.is_valid()
                && selected_profile.is_valid();
        }

        [[nodiscard]] constexpr bool accepted() const noexcept
        {
            return is_valid()
                && configuration_valid
                && capabilities_satisfied
                && protocol_requirements_satisfied
                && binding_requirements_satisfied;
        }
    };
}

#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/administrative/TAsccComponentDescriptor.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"

namespace assembler::communication_context
{
    struct TAsccManagerialReadinessView final
    {
        TAsccComponentDescriptor component{};
        TAsccComponentProfileId selected_profile{TAsccComponentProfileId::invalid()};
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        bool configuration_valid{false};
        bool capabilities_satisfied{false};
        bool protocol_requirements_satisfied{false};
        bool binding_requirements_satisfied{false};
        bool diagnostics_available{false};
        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return component.is_valid()
                && selected_profile.is_valid()
                && status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && status == TAsccComponentReadinessStatus::ready
                && configuration_valid
                && capabilities_satisfied
                && protocol_requirements_satisfied
                && binding_requirements_satisfied;
        }
    };
}

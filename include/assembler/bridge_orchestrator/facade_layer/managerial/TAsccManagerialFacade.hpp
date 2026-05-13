#pragma once

#include "assembler/communication_context/facade_layer/managerial/TAsccComponentAdmission.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccManagerialReadinessView.hpp"

namespace assembler::communication_context
{
    struct TAsccManagerialFacade final
    {
        TAsccComponentAdmission admission{};
        TAsccManagerialReadinessView readiness{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return admission.is_valid()
                && readiness.is_valid();
        }

        [[nodiscard]] constexpr bool admits_component() const noexcept
        {
            return admission.accepted()
                && readiness.ready();
        }
    };
}

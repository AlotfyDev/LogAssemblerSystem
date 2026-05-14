#pragma once

#include "assembler/communication_context/facade_layer/managerial/TAsccRegistryReadinessView.hpp"
#include "assembler/communication_context/registries/reports/TRegistrySetReadinessReport.hpp"

/**
 * @file TAsccRegistryAdmissionPolicy.hpp
 * @brief Managerial facade policy for admitting ASCC registry readiness.
 *
 * @section purpose Purpose
 * Converts registry-set readiness reports into facade readiness views.
 */

namespace assembler::communication_context
{
    struct TAsccRegistryAdmissionPolicy final
    {
        [[nodiscard]] static constexpr TAsccRegistryReadinessView admit(
            TRegistrySetReadinessReport report) noexcept
        {
            return TAsccRegistryReadinessView::from_report(report);
        }
    };
}

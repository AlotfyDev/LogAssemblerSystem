#pragma once

#include "assembler/communication_context/registries/reports/TRegistryReadinessReport.hpp"

/**
 * @file TRegistryAdmissionPolicy.hpp
 * @brief Managerial policy for accepting registry evidence into component readiness.
 *
 * @section purpose Purpose
 * Provides a bounded rule for interpreting registry readiness reports without
 * turning registries into service locators.
 */

namespace assembler::communication_context
{
    struct TRegistryAdmissionPolicy final
    {
        [[nodiscard]] static constexpr bool admits(
            TRegistryReadinessReport report) noexcept
        {
            return report.ready();
        }
    };
}

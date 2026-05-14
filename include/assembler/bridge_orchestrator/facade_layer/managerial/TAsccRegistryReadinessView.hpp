#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/registries/reports/TRegistrySetReadinessReport.hpp"

/**
 * @file TAsccRegistryReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC registries.
 *
 * @section purpose Purpose
 * Projects grouped registry readiness into ASCC component admission form.
 */

namespace assembler::communication_context
{
    struct TAsccRegistryReadinessView final
    {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TRegistrySetReadinessReport registry_set_report{};
        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && status == TAsccComponentReadinessStatus::ready
                && registry_set_report.ready();
        }

        [[nodiscard]] static constexpr TAsccRegistryReadinessView from_report(
            TRegistrySetReadinessReport report,
            std::string_view note = {}) noexcept
        {
            return TAsccRegistryReadinessView{
                report.ready()
                    ? TAsccComponentReadinessStatus::ready
                    : TAsccComponentReadinessStatus::blocked,
                report,
                note
            };
        }
    };
}

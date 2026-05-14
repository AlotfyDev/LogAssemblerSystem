#pragma once

#include <string_view>

/**
 * @file TRegistrySetReadinessReport.hpp
 * @brief Component-level readiness report for the ASCC grouped registry set.
 *
 * @section purpose Purpose
 * Summarizes readiness of the grouped Communication Context registries for
 * component admission.
 *
 * It reports counts and readiness dimensions only; it does not expose mutable
 * registry handles and does not resolve services.
 */

namespace assembler::communication_context
{
    struct TRegistrySetReadinessReport final
    {
        std::size_t total_registered{0u};
        bool channels_ready{false};
        bool bindings_ready{false};
        bool sessions_ready{false};
        bool protocols_ready{false};
        bool bridges_ready{false};
        std::string_view report_note{};

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return channels_ready
                && bindings_ready
                && sessions_ready
                && protocols_ready
                && bridges_ready;
        }
    };
}

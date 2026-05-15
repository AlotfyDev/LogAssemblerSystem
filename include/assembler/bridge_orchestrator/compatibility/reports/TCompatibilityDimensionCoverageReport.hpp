#pragma once
#include <string_view>

/**
 * @file TCompatibilityDimensionCoverageReport.hpp
 * @brief Reports which ASCC compatibility dimensions were evaluated.
 */
namespace assembler::communication_context {
    struct TCompatibilityDimensionCoverageReport final {
        bool participant_checked{false};
        bool channel_checked{false};
        bool binding_checked{false};
        bool obligation_checked{false};
        bool carrier_checked{false};
        bool session_checked{false};
        bool protocol_checked{false};
        std::string_view report_name{"compatibility_dimension_coverage"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !report_name.empty(); }
        [[nodiscard]] constexpr bool full_component_coverage() const noexcept {
            return participant_checked && channel_checked && binding_checked && obligation_checked && carrier_checked && session_checked && protocol_checked;
        }
    };
}

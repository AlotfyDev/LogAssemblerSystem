#pragma once
#include <cstddef>
#include <string_view>

/**
 * @file TProtocolPlanReadinessReport.hpp
 * @brief Readiness report for protocol plan and requirement bindings.
 */
namespace assembler::communication_context {
    struct TProtocolPlanReadinessReport final {
        std::size_t plan_step_count{0u};
        std::size_t bound_step_count{0u};
        std::size_t missing_required_bindings{0u};
        bool plan_valid{false};
        bool requirements_valid{false};
        std::string_view report_name{"protocol_plan_readiness_report"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !report_name.empty(); }
        [[nodiscard]] constexpr bool ready() const noexcept {
            return is_valid() && plan_valid && requirements_valid && missing_required_bindings == 0u && bound_step_count >= plan_step_count;
        }
    };
}

#pragma once
#include <string_view>
#include "assembler/communication_context/sessions/results/TSessionResult.hpp"
#include "assembler/communication_context/sessions/status/TSessionStatus.hpp"

/**
 * @file TSessionLifecycleTransitionReport.hpp
 * @brief Evidence report for one ASCC session lifecycle transition.
 */
namespace assembler::communication_context {
    struct TSessionLifecycleTransitionReport final {
        TSessionStatus before{TSessionStatus::unknown};
        TSessionStatus after{TSessionStatus::unknown};
        TSessionResult result{};
        bool accepted{false};
        std::string_view note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return before != TSessionStatus::unknown && after != TSessionStatus::unknown; }
        [[nodiscard]] constexpr bool succeeded() const noexcept { return is_valid() && accepted && result.succeeded(); }
    };
}

#pragma once
#include "assembler/communication_context/facade_layer/managerial/TAsccSessionReadinessView.hpp"
#include "assembler/communication_context/sessions/reports/TSessionLifecycleTransitionReport.hpp"
#include "assembler/communication_context/sessions/runtime/TSessionRuntimeContext.hpp"

/**
 * @file TSessionRuntimeReport.hpp
 * @brief Aggregate session runtime evidence report.
 */
namespace assembler::communication_context {
    struct TSessionRuntimeReport final {
        TSessionRuntimeContext context{};
        TSessionLifecycleTransitionReport last_transition{};
        TAsccSessionReadinessView readiness{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return context.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return context.ready() && readiness.ready(); }
    };
}

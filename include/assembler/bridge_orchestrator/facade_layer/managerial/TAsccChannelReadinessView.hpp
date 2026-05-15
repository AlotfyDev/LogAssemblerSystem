#pragma once
#include <string_view>
#include "assembler/communication_context/channels/reports/TChannelRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"

/**
 * @file TAsccChannelReadinessView.hpp
 * @brief Managerial facade readiness projection for ASCC channels.
 */
namespace assembler::communication_context {
    struct TAsccChannelReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TChannelRuntimeReport runtime_report{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown && runtime_report.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status == TAsccComponentReadinessStatus::ready && runtime_report.ready(); }
        [[nodiscard]] static constexpr TAsccChannelReadinessView from_report(TChannelRuntimeReport report, std::string_view note = {}) noexcept {
            return {report.ready() ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, report, note};
        }
    };
}

#pragma once
#include <string_view>
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/participants/reports/TParticipantRuntimeReport.hpp"

/**
 * @file TAsccParticipantReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC participants.
 */
namespace assembler::communication_context {
    struct TAsccParticipantReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TParticipantRuntimeReport runtime_report{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown && runtime_report.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status == TAsccComponentReadinessStatus::ready && runtime_report.ready(); }
        [[nodiscard]] static constexpr TAsccParticipantReadinessView from_report(TParticipantRuntimeReport report, std::string_view note = {}) noexcept {
            return {report.ready() ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, report, note};
        }
    };
}

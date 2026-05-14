#pragma once
#include <string_view>
#include "assembler/communication_context/facade_layer/managerial/TAsccBindingReadinessView.hpp"
/**
 * @file TAsccBindingEvidenceAdapter.hpp
 * @brief Common facade adapter that builds ASCC binding readiness evidence.
 *
 * Converts binding composition reports and session-open profiles into a
 * facade-safe `TAsccBindingReadinessView`.
 */
namespace assembler::communication_context {
struct TAsccBindingEvidenceAdapter final {
    [[nodiscard]] static constexpr TAsccBindingReadinessView to_readiness_view(
        TBindingCompositionReadinessReport composition_report,
        TBindingSessionOpenProfile session_profile,
        bool binding_known, bool role_map_ready, bool obligation_surfaces_ready,
        std::string_view note = {}) noexcept {
        const bool ready = binding_known && composition_report.passed() && session_profile.can_open_session() && role_map_ready && obligation_surfaces_ready;
        return {ready ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked,
                composition_report, session_profile, binding_known, role_map_ready, obligation_surfaces_ready, note};
    }
};
}

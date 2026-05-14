#pragma once
#include <string_view>
#include "assembler/communication_context/bindings/composition/TBindingCompositionReadinessReport.hpp"
#include "assembler/communication_context/bindings/session/TBindingSessionOpenProfile.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
/**
 * @file TAsccBindingReadinessView.hpp
 * @brief Managerial facade readiness view for a selected ASCC binding.
 *
 * Projects binding readiness into facade form: composition match,
 * session-open readiness, role mapping, obligation mapping, and admission state.
 */
namespace assembler::communication_context {
struct TAsccBindingReadinessView final {
    TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
    TBindingCompositionReadinessReport composition_report{};
    TBindingSessionOpenProfile session_open_profile{};
    bool binding_known{false}, role_map_ready{false}, obligation_surfaces_ready{false};
    std::string_view readiness_note{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return status!=TAsccComponentReadinessStatus::unknown && composition_report.is_valid() && session_open_profile.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status==TAsccComponentReadinessStatus::ready && binding_known && composition_report.passed() && session_open_profile.can_open_session() && role_map_ready && obligation_surfaces_ready; }
};
}

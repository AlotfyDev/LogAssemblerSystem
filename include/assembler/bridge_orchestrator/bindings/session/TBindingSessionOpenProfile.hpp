#pragma once
#include <string_view>
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"
/**
 * @file TBindingSessionOpenProfile.hpp
 * @brief Descriptor describing how a binding may participate in session opening.
 *
 * Captures session-opening readiness of a selected binding: validity,
 * compatibility, materialization, and selected local session policy.
 */
namespace assembler::communication_context {
struct TBindingSessionOpenProfile final {
    TSessionPolicy session_policy{};
    bool binding_valid{false}, binding_compatible{false}, binding_materialized{false};
    std::string_view profile_name{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return session_policy.is_valid() && binding_valid && !profile_name.empty(); }
    [[nodiscard]] constexpr bool can_open_declaration_session() const noexcept { return is_valid() && binding_compatible && session_policy.allows_open_from_compatible_binding(); }
    [[nodiscard]] constexpr bool can_open_materialized_session() const noexcept { return is_valid() && binding_compatible && binding_materialized && session_policy.requires_materialized_binding(); }
    [[nodiscard]] constexpr bool can_open_session() const noexcept { return can_open_declaration_session() || can_open_materialized_session(); }
};
}

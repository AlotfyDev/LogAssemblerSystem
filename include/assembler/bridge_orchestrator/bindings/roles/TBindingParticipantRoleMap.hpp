#pragma once
#include <string_view>
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
/**
 * @file TBindingParticipantRoleMap.hpp
 * @brief Descriptor mapping binding source/target sides to ASCC participant roles.
 *
 * Connects concrete binding sides to protocol participant requirements.
 * It does not resolve runtime participant instances or invoke endpoints.
 */
namespace assembler::communication_context {
struct TBindingParticipantRoleMap final {
    TParticipantRole source_role{TParticipantRole::unknown};
    TParticipantRole target_role{TParticipantRole::unknown};
    std::string_view map_name{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return source_role!=TParticipantRole::unknown && target_role!=TParticipantRole::unknown && source_role!=target_role; }
    [[nodiscard]] constexpr bool contains(TParticipantRole role) const noexcept { return source_role==role || target_role==role; }
    [[nodiscard]] static constexpr TBindingParticipantRoleMap content_to_receiver(std::string_view name="content_to_receiver_binding_roles") noexcept { return {TParticipantRole::content_provider,TParticipantRole::receiver_provider,name}; }
};
}

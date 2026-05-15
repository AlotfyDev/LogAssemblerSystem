#pragma once
#include <string_view>
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"

/**
 * @file TParticipantRoleBindingMap.hpp
 * @brief Runtime descriptor mapping a participant to a binding side/role.
 */
namespace assembler::communication_context {
    struct TParticipantRoleBindingMap final {
        std::uint64_t participant_id{0u};
        TParticipantRole role{TParticipantRole::unknown};
        std::string_view binding_side{};
        std::string_view binding_family{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return participant_id != 0u && role != TParticipantRole::unknown && !binding_side.empty(); }
        [[nodiscard]] static constexpr TParticipantRoleBindingMap from_participant(const TParticipant& p, std::string_view side, std::string_view family = {}) noexcept {
            return {p.participant_id, p.role, side, family};
        }
    };
}

#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"

/**
 * @file TAsccParticipantCatalogView.hpp
 * @brief Administrative facade catalog for ASCC participant roles and capabilities.
 */
namespace assembler::communication_context {
    template <std::size_t Capacity>
    struct TAsccParticipantCatalogView final {
        std::array<TParticipantRole, Capacity> roles{};
        std::array<TParticipantCapabilityKind, Capacity> capabilities{};
        std::size_t role_count{0u};
        std::size_t capability_count{0u};
        std::string_view catalog_name{"ascc_participant_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !catalog_name.empty() && role_count <= Capacity && capability_count <= Capacity; }
        constexpr bool add_role(TParticipantRole role) noexcept { if (role_count >= Capacity || role == TParticipantRole::unknown) return false; roles[role_count++] = role; return true; }
        constexpr bool add_capability(TParticipantCapabilityKind cap) noexcept { if (capability_count >= Capacity || cap == TParticipantCapabilityKind::unknown) return false; capabilities[capability_count++] = cap; return true; }
    };
}

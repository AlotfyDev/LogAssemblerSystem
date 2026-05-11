#pragma once
#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "TContainerFamilyShape.hpp"

/*
    TDefaultEmptyContainerProfileReport.hpp

    Responsibility:
        Evidence that BundleAgent provides a default empty container shape/profile.

    Non-ownership:
        Does not reset concrete containers; Moderator performs reset later.
*/
namespace assembler {
namespace circulation_mechanism {

struct TDefaultEmptyContainerProfileReport final {
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TContainerFamilyShape default_empty_shape{};
    bool profile_available{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return bundle_agent_id.is_valid() && family_id.is_valid() && default_empty_shape.is_valid();
    }

    [[nodiscard]] constexpr bool ready() const noexcept {
        return is_valid() && profile_available;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

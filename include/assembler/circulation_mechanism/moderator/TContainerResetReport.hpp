#pragma once
#include "TContainerResetPlan.hpp"
#include "TModeratorId.hpp"

/*
    TContainerResetReport.hpp

    Responsibility:
        Evidence of a reset plan/result accepted or rejected by Moderator.

    Non-ownership:
        Report does not execute reset and does not mutate registry.
*/
namespace assembler {
namespace circulation_mechanism {

struct TContainerResetReport final {
    TModeratorId moderator_id{};
    TContainerResetPlan plan{};
    bool applied{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return moderator_id.is_valid() && plan.is_valid();
    }
    [[nodiscard]] constexpr bool reset_applied() const noexcept {
        return is_valid() && plan.accepted() && applied && plan.after == TContainerState::default_empty;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

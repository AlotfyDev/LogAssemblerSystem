#pragma once

#include "TModeratorId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

/*
    TContainerResetReport.hpp

    Responsibility:
        Records evidence that a moderator reset operation was planned or applied.

    Does not own:
        - Reset algorithm.
        - Recovery behavior.
        - Registry mutation.
*/

namespace assembler {
namespace circulation_mechanism {

struct TContainerResetReport final
{
    TModeratorId moderator_id{};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TContainerState before{TContainerState::reset_pending};
    TContainerState after{TContainerState::default_empty};
    bool accepted{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return moderator_id.is_valid()
            && container_id.is_valid()
            && registry_index.is_valid();
    }

    [[nodiscard]] constexpr bool reset_applied() const noexcept
    {
        return accepted && after == TContainerState::default_empty;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once

#include "TModeratorReadinessView.hpp"

/*
    TModeratedContainerView.hpp

    Responsibility:
        Provides an approved read-only projection of the container moderated by
        a moderator.

    Does not own:
        - Container mutable internals.
*/

namespace assembler {
namespace circulation_mechanism {

struct TModeratedContainerView final
{
    TModeratorReadinessView readiness{};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return readiness.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

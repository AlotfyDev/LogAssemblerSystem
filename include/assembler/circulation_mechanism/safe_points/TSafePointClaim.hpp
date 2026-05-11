#pragma once

#include "TSafePointId.hpp"
#include "TSafePointKind.hpp"

/*
    TSafePointClaim.hpp

    Responsibility:
        Represents a successful claim of a safe point for a specific operation kind.

    Non-ownership:
        The claim does not execute the operation. It is a permission artifact
        consumed by the operation owner.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSafePointClaim final
{
    TSafePointId id{};
    TSafePointKind kind{TSafePointKind::container_reset};
    std::uint64_t generation{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return id.is_valid();
    }
};

} // namespace circulation_mechanism
} // namespace assembler

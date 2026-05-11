#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>

/*
    TViewId.hpp

    Delivery:
        CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

    Current responsibility:
        Defines `TViewId` as the production-grade typed identity for read-only
        view artifacts in the Circulation Mechanism Engine.

    Production capabilities:
        - Strongly typed view identity atom.
        - Invalid value policy.
        - constexpr invalid()/from_raw()/raw()/value_or()/is_valid().
        - Equality, inequality, ordering.
        - std::hash specialization.
        - No implicit conversion to raw integer.

    Architectural role:
        Identifies a view artifact or view descriptor.

    Explicit non-ownership:
        - Does not own viewed state.
        - Does not grant mutation.
        - Does not extend object lifetime.
        - Does not prove report evidence.
        - Does not imply boundary export permission.
*/

namespace assembler {
namespace circulation_mechanism {


struct TViewId final
{
    using value_type = std::uint64_t;

    static constexpr value_type k_invalid_value = static_cast<value_type>(0);

    value_type value{k_invalid_value};

    constexpr TViewId() noexcept = default;
    constexpr explicit TViewId(value_type input_value) noexcept : value(input_value) {}

    [[nodiscard]] static constexpr TViewId invalid() noexcept
    {
        return TViewId{k_invalid_value};
    }

    [[nodiscard]] static constexpr TViewId from_raw(value_type input_value) noexcept
    {
        return TViewId{input_value};
    }

    [[nodiscard]] constexpr value_type raw() const noexcept
    {
        return value;
    }

    [[nodiscard]] constexpr value_type value_or(value_type fallback_value) const noexcept
    {
        return is_valid() ? value : fallback_value;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return value != k_invalid_value;
    }

    [[nodiscard]] explicit constexpr operator bool() const noexcept
    {
        return is_valid();
    }

    [[nodiscard]] friend constexpr bool operator==(TViewId lhs, TViewId rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    [[nodiscard]] friend constexpr bool operator!=(TViewId lhs, TViewId rhs) noexcept
    {
        return !(lhs == rhs);
    }

    [[nodiscard]] friend constexpr bool operator<(TViewId lhs, TViewId rhs) noexcept
    {
        return lhs.value < rhs.value;
    }
};

} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template <>
struct hash<assembler::circulation_mechanism::TViewId>
{
    [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TViewId& input) const noexcept
    {
        return std::hash<assembler::circulation_mechanism::TViewId::value_type>{}(input.raw());
    }
};
} // namespace std

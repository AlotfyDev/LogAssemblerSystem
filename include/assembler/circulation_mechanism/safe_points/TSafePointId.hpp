#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>

/*
    TSafePointId.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Defines `TSafePointId` as the production-grade typed identity for local
        safe-point artifacts.

    Production capabilities:
        - Strongly typed safe-point identity atom.
        - invalid()/from_raw()/raw()/value_or()/is_valid().
        - Equality, inequality, ordering.
        - std::hash specialization.

    Architectural role:
        Identifies a safe-point condition or claim record. It is not the guarded
        operation itself.

    Explicit non-ownership:
        - Does not execute reset, scaling, eviction, registry rebuild, or reference invalidation.
        - Does not own component state.
        - Does not create global stop-the-world behavior.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSafePointId final
{
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;

    value_type value{k_invalid_value};

    constexpr TSafePointId() noexcept = default;
    constexpr explicit TSafePointId(value_type input_value) noexcept : value(input_value) {}

    [[nodiscard]] static constexpr TSafePointId invalid() noexcept { return TSafePointId{k_invalid_value}; }
    [[nodiscard]] static constexpr TSafePointId from_raw(value_type input_value) noexcept { return TSafePointId{input_value}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr value_type value_or(value_type fallback_value) const noexcept { return is_valid() ? value : fallback_value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] explicit constexpr operator bool() const noexcept { return is_valid(); }

    [[nodiscard]] friend constexpr bool operator==(TSafePointId lhs, TSafePointId rhs) noexcept { return lhs.value == rhs.value; }
    [[nodiscard]] friend constexpr bool operator!=(TSafePointId lhs, TSafePointId rhs) noexcept { return !(lhs == rhs); }
    [[nodiscard]] friend constexpr bool operator<(TSafePointId lhs, TSafePointId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template <>
struct hash<assembler::circulation_mechanism::TSafePointId>
{
    [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TSafePointId& input) const noexcept
    {
        return std::hash<assembler::circulation_mechanism::TSafePointId::value_type>{}(input.raw());
    }
};
} // namespace std

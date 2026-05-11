#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>

/*
    TDiagnosticIssueId.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines production-grade typed identity for diagnostic issues.

    Production capabilities:
        - Strongly typed diagnostic issue identity.
        - invalid()/from_raw()/raw()/value_or()/is_valid().
        - Equality, inequality, ordering.
        - std::hash specialization.

    Explicit non-ownership:
        - Does not store diagnostics.
        - Does not execute recovery.
        - Does not log/export telemetry.
        - Does not mutate runtime state.
*/

namespace assembler {
namespace circulation_mechanism {


struct TDiagnosticIssueId final
{
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;

    value_type value{k_invalid_value};

    constexpr TDiagnosticIssueId() noexcept = default;
    constexpr explicit TDiagnosticIssueId(value_type input_value) noexcept : value(input_value) {}

    [[nodiscard]] static constexpr TDiagnosticIssueId invalid() noexcept { return TDiagnosticIssueId{k_invalid_value}; }
    [[nodiscard]] static constexpr TDiagnosticIssueId from_raw(value_type input_value) noexcept { return TDiagnosticIssueId{input_value}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr value_type value_or(value_type fallback_value) const noexcept { return is_valid() ? value : fallback_value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] explicit constexpr operator bool() const noexcept { return is_valid(); }

    [[nodiscard]] friend constexpr bool operator==(TDiagnosticIssueId lhs, TDiagnosticIssueId rhs) noexcept { return lhs.value == rhs.value; }
    [[nodiscard]] friend constexpr bool operator!=(TDiagnosticIssueId lhs, TDiagnosticIssueId rhs) noexcept { return !(lhs == rhs); }
    [[nodiscard]] friend constexpr bool operator<(TDiagnosticIssueId lhs, TDiagnosticIssueId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template <>
struct hash<assembler::circulation_mechanism::TDiagnosticIssueId>
{
    [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TDiagnosticIssueId& input) const noexcept
    {
        return std::hash<assembler::circulation_mechanism::TDiagnosticIssueId::value_type>{}(input.raw());
    }
};
}

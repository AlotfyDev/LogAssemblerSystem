#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>

/*
    TReportId.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Defines `TReportId` as the production-grade typed identity for report
        artifacts in the Circulation Mechanism Engine.

    Production capabilities:
        - Strongly typed report identity atom.
        - Invalid value policy.
        - constexpr invalid()/from_raw()/raw()/value_or()/is_valid().
        - Equality, inequality, ordering.
        - std::hash specialization.
        - No implicit conversion to raw integer.

    Architectural role:
        Identifies a report/evidence artifact. It does not prove what the
        report claims; proof is scoped by `TReportDescriptor`.

    Explicit non-ownership:
        - Does not store report payloads.
        - Does not emit telemetry.
        - Does not execute recovery.
        - Does not prove bridge, receiver, persistence, or read-side success.
*/

namespace assembler {
namespace circulation_mechanism {


struct TReportId final
{
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = static_cast<value_type>(0);

    value_type value{k_invalid_value};

    constexpr TReportId() noexcept = default;
    constexpr explicit TReportId(value_type input_value) noexcept : value(input_value) {}

    [[nodiscard]] static constexpr TReportId invalid() noexcept
    {
        return TReportId{k_invalid_value};
    }

    [[nodiscard]] static constexpr TReportId from_raw(value_type input_value) noexcept
    {
        return TReportId{input_value};
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

    [[nodiscard]] friend constexpr bool operator==(TReportId lhs, TReportId rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    [[nodiscard]] friend constexpr bool operator!=(TReportId lhs, TReportId rhs) noexcept
    {
        return !(lhs == rhs);
    }

    [[nodiscard]] friend constexpr bool operator<(TReportId lhs, TReportId rhs) noexcept
    {
        return lhs.value < rhs.value;
    }
};

} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template <>
struct hash<assembler::circulation_mechanism::TReportId>
{
    [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TReportId& input) const noexcept
    {
        return std::hash<assembler::circulation_mechanism::TReportId::value_type>{}(input.raw());
    }
};
} // namespace std

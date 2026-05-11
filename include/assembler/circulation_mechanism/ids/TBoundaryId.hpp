#pragma once

    #include <cstdint>
    #include <functional>
    #include <limits>
    #include <type_traits>

    /*
        TBoundaryId.hpp

        Delivery:
            CME-IDS-PROD-W01 — Production Identity Contract

        Current responsibility:
            Defines `TBoundaryId` as a production-grade typed identity/locator
            atom in the Circulation Mechanism Engine.

        Semantic role:
            Boundary identity for CME ingress/dispatch/binding artifacts.

        Production capabilities:
            - Strongly typed wrapper over an unsigned raw value.
            - Explicit invalid-value policy.
            - constexpr construction and validation.
            - raw() accessor for controlled serialization/diagnostics.
            - value_or() fallback helper.
            - invalid() factory.
            - from_raw() factory.
            - equality, inequality, and ordering operators.
            - type-level distinction from other ID/index types.
            - std::hash specialization.
            - static traits for identity vs locator classification.
            - compile-time friendliness for header-only C++17 usage.

        Valid usage:
            Use to correlate boundary descriptors, binding reports, and boundary diagnostics.

        Explicit invalid usage:
            Do not use as bridge session id, receiver id, payload id, or adapter lifetime owner.

        Non-ownership:
            - Does not own runtime storage.
            - Does not own object lifetime.
            - Does not execute behavior.
            - Does not grant mutable access.
            - Does not prove bridge, receiver, persistence, or read-side success.
            - Does not replace scoped access references.

        Anti-collapse rule:
            `TBoundaryId` may identify, correlate, or locate according to its
            declared semantic role. It must never become a runtime actor,
            mutable handle, bridge protocol id, receiver lifecycle id, or
            downstream persistence key unless a later contract explicitly
            creates a separate type for that purpose.
    */

    namespace assembler {
namespace circulation_mechanism {


    struct TBoundaryId final
    {
        using value_type = std::uint64_t;

        static constexpr value_type k_invalid_value = static_cast<value_type>(0);
        static constexpr bool k_is_identity_atom = true;
        static constexpr bool k_is_locator_atom = false;

        value_type value{k_invalid_value};

        constexpr TBoundaryId() noexcept = default;

        constexpr explicit TBoundaryId(value_type input_value) noexcept
            : value(input_value)
        {
        }

        [[nodiscard]] static constexpr TBoundaryId invalid() noexcept
        {
            return TBoundaryId{k_invalid_value};
        }

        [[nodiscard]] static constexpr TBoundaryId from_raw(value_type input_value) noexcept
        {
            return TBoundaryId{input_value};
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

        [[nodiscard]] friend constexpr bool operator==(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return !(lhs == rhs);
        }

        [[nodiscard]] friend constexpr bool operator<(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return lhs.value < rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator>(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return rhs < lhs;
        }

        [[nodiscard]] friend constexpr bool operator<=(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return !(rhs < lhs);
        }

        [[nodiscard]] friend constexpr bool operator>=(TBoundaryId lhs, TBoundaryId rhs) noexcept
        {
            return !(lhs < rhs);
        }
    };

    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template <>
    struct hash<assembler::circulation_mechanism::TBoundaryId>
    {
        [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TBoundaryId& input) const noexcept
        {
            return std::hash<assembler::circulation_mechanism::TBoundaryId::value_type>{}(input.raw());
        }
    };
    } // namespace std

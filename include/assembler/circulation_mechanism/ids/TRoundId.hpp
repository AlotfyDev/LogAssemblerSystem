#pragma once

    #include <cstdint>
    #include <functional>
    #include <limits>
    #include <type_traits>

    /*
        TRoundId.hpp

        Delivery:
            CME-IDS-PROD-W01 — Production Identity Contract

        Current responsibility:
            Defines `TRoundId` as a production-grade typed identity/locator
            atom in the Circulation Mechanism Engine.

        Semantic role:
            Identity of a circulation round context.

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
            Use for round state, round membership, waiting-list draining, and round-scoped reference traces.

        Explicit invalid usage:
            Do not use as scheduler id, thread id, dispatcher id, or bridge session id.

        Non-ownership:
            - Does not own runtime storage.
            - Does not own object lifetime.
            - Does not execute behavior.
            - Does not grant mutable access.
            - Does not prove bridge, receiver, persistence, or read-side success.
            - Does not replace scoped access references.

        Anti-collapse rule:
            `TRoundId` may identify, correlate, or locate according to its
            declared semantic role. It must never become a runtime actor,
            mutable handle, bridge protocol id, receiver lifecycle id, or
            downstream persistence key unless a later contract explicitly
            creates a separate type for that purpose.
    */

    namespace assembler {
namespace circulation_mechanism {


    struct TRoundId final
    {
        using value_type = std::uint64_t;

        static constexpr value_type k_invalid_value = static_cast<value_type>(0);
        static constexpr bool k_is_identity_atom = true;
        static constexpr bool k_is_locator_atom = false;

        value_type value{k_invalid_value};

        constexpr TRoundId() noexcept = default;

        constexpr explicit TRoundId(value_type input_value) noexcept
            : value(input_value)
        {
        }

        [[nodiscard]] static constexpr TRoundId invalid() noexcept
        {
            return TRoundId{k_invalid_value};
        }

        [[nodiscard]] static constexpr TRoundId from_raw(value_type input_value) noexcept
        {
            return TRoundId{input_value};
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

        [[nodiscard]] friend constexpr bool operator==(TRoundId lhs, TRoundId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(TRoundId lhs, TRoundId rhs) noexcept
        {
            return !(lhs == rhs);
        }

        [[nodiscard]] friend constexpr bool operator<(TRoundId lhs, TRoundId rhs) noexcept
        {
            return lhs.value < rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator>(TRoundId lhs, TRoundId rhs) noexcept
        {
            return rhs < lhs;
        }

        [[nodiscard]] friend constexpr bool operator<=(TRoundId lhs, TRoundId rhs) noexcept
        {
            return !(rhs < lhs);
        }

        [[nodiscard]] friend constexpr bool operator>=(TRoundId lhs, TRoundId rhs) noexcept
        {
            return !(lhs < rhs);
        }
    };

    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template <>
    struct hash<assembler::circulation_mechanism::TRoundId>
    {
        [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TRoundId& input) const noexcept
        {
            return std::hash<assembler::circulation_mechanism::TRoundId::value_type>{}(input.raw());
        }
    };
    } // namespace std

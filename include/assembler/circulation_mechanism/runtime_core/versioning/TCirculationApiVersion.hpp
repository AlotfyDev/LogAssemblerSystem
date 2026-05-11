#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationApiVersion.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Current responsibility:
            Identifies an API compatibility version.

        Production capabilities:
            - typed identity/version atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not start runtime execution.
            - Does not own PreBridge behavior.
            - Does not own ReadSide behavior.
            - Does not mutate component internals.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TCirculationApiVersion final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationApiVersion() noexcept = default;
        constexpr explicit TCirculationApiVersion(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationApiVersion invalid() noexcept { return TCirculationApiVersion{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationApiVersion from_raw(value_type input) noexcept { return TCirculationApiVersion{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationApiVersion lhs, TCirculationApiVersion rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationApiVersion lhs, TCirculationApiVersion rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TCirculationApiVersion> {
        std::size_t operator()(const assembler::circulation_mechanism::TCirculationApiVersion& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TCirculationApiVersion::value_type>{}(input.raw());
        }
    };
    }

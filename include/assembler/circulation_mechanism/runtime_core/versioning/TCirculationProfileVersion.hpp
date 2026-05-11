#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationProfileVersion.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Current responsibility:
            Identifies a profile/configuration version.

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

    struct TCirculationProfileVersion final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationProfileVersion() noexcept = default;
        constexpr explicit TCirculationProfileVersion(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationProfileVersion invalid() noexcept { return TCirculationProfileVersion{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationProfileVersion from_raw(value_type input) noexcept { return TCirculationProfileVersion{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationProfileVersion lhs, TCirculationProfileVersion rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationProfileVersion lhs, TCirculationProfileVersion rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TCirculationProfileVersion> {
        std::size_t operator()(const assembler::circulation_mechanism::TCirculationProfileVersion& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TCirculationProfileVersion::value_type>{}(input.raw());
        }
    };
    }

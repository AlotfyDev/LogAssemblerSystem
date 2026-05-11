#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationRuntimeId.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Current responsibility:
            Identifies one configured circulation runtime instance descriptor.

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

    struct TCirculationRuntimeId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationRuntimeId() noexcept = default;
        constexpr explicit TCirculationRuntimeId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationRuntimeId invalid() noexcept { return TCirculationRuntimeId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationRuntimeId from_raw(value_type input) noexcept { return TCirculationRuntimeId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationRuntimeId lhs, TCirculationRuntimeId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationRuntimeId lhs, TCirculationRuntimeId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TCirculationRuntimeId> {
        std::size_t operator()(const assembler::circulation_mechanism::TCirculationRuntimeId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TCirculationRuntimeId::value_type>{}(input.raw());
        }
    };
    }

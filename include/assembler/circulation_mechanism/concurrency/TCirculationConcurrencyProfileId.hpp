#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationConcurrencyProfileId.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Current responsibility:
            Identifies one circulation concurrency policy profile.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not create threads.
            - Does not schedule work.
            - Does not lock or unlock runtime objects.
            - Does not execute bridge or receiver runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    struct TCirculationConcurrencyProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationConcurrencyProfileId() noexcept = default;
        constexpr explicit TCirculationConcurrencyProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationConcurrencyProfileId invalid() noexcept { return TCirculationConcurrencyProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationConcurrencyProfileId from_raw(value_type input) noexcept { return TCirculationConcurrencyProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationConcurrencyProfileId lhs, TCirculationConcurrencyProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationConcurrencyProfileId lhs, TCirculationConcurrencyProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::concurrency::TCirculationConcurrencyProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::concurrency::TCirculationConcurrencyProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::concurrency::TCirculationConcurrencyProfileId::value_type>{}(input.raw());
        }
    };
    }

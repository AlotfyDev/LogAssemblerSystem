#pragma once

    #include <cstdint>
    #include <functional>
    #include <type_traits>

    /*
        TCapacityProfileId.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines identity for a capacity profile.

        Production capabilities:
            - Strongly typed capacity identity atom.
            - invalid()/from_raw()/raw()/value_or()/is_valid().
            - Equality, inequality, ordering.
            - std::hash specialization.
            - No implicit conversion to raw integer.

        Explicit non-ownership:
            - Does not allocate containers.
            - Does not mutate registry.
            - Does not execute scaling.
            - Does not own bridge/read-side runtime.
    */

    namespace assembler {
namespace circulation_mechanism {


    struct TCapacityProfileId final
    {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;

        value_type value{k_invalid_value};

        constexpr TCapacityProfileId() noexcept = default;
        constexpr explicit TCapacityProfileId(value_type input_value) noexcept : value(input_value) {}

        [[nodiscard]] static constexpr TCapacityProfileId invalid() noexcept { return TCapacityProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCapacityProfileId from_raw(value_type input_value) noexcept { return TCapacityProfileId{input_value}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr value_type value_or(value_type fallback_value) const noexcept { return is_valid() ? value : fallback_value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] explicit constexpr operator bool() const noexcept { return is_valid(); }

        [[nodiscard]] friend constexpr bool operator==(TCapacityProfileId lhs, TCapacityProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCapacityProfileId lhs, TCapacityProfileId rhs) noexcept { return !(lhs == rhs); }
        [[nodiscard]] friend constexpr bool operator<(TCapacityProfileId lhs, TCapacityProfileId rhs) noexcept { return lhs.value < rhs.value; }
    };

    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template <>
    struct hash<assembler::circulation_mechanism::TCapacityProfileId>
    {
        [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TCapacityProfileId& input) const noexcept
        {
            return std::hash<assembler::circulation_mechanism::TCapacityProfileId::value_type>{}(input.raw());
        }
    };
    } // namespace std

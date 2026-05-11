#pragma once

    #include <cstdint>
    #include <functional>
    #include <type_traits>

    /*
        TCapacityGenerationId.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines identity for a capacity/profile generation.

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


    struct TCapacityGenerationId final
    {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;

        value_type value{k_invalid_value};

        constexpr TCapacityGenerationId() noexcept = default;
        constexpr explicit TCapacityGenerationId(value_type input_value) noexcept : value(input_value) {}

        [[nodiscard]] static constexpr TCapacityGenerationId invalid() noexcept { return TCapacityGenerationId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCapacityGenerationId from_raw(value_type input_value) noexcept { return TCapacityGenerationId{input_value}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr value_type value_or(value_type fallback_value) const noexcept { return is_valid() ? value : fallback_value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] explicit constexpr operator bool() const noexcept { return is_valid(); }

        [[nodiscard]] friend constexpr bool operator==(TCapacityGenerationId lhs, TCapacityGenerationId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCapacityGenerationId lhs, TCapacityGenerationId rhs) noexcept { return !(lhs == rhs); }
        [[nodiscard]] friend constexpr bool operator<(TCapacityGenerationId lhs, TCapacityGenerationId rhs) noexcept { return lhs.value < rhs.value; }
    };

    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template <>
    struct hash<assembler::circulation_mechanism::TCapacityGenerationId>
    {
        [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TCapacityGenerationId& input) const noexcept
        {
            return std::hash<assembler::circulation_mechanism::TCapacityGenerationId::value_type>{}(input.raw());
        }
    };
    } // namespace std

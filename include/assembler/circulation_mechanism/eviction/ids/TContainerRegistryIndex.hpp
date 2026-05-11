#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TContainerRegistryIndex.hpp

        Delivery:
            CME-EVICTION-PROD-W01 — Production SafePoint Candidate Contract

        Current responsibility:
            Identifies candidate registry index.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not mutate registry.
            - Does not execute eviction by itself.
            - Does not delete persistence.
            - Does not own bridge/read-side retry.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TContainerRegistryIndex final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TContainerRegistryIndex() noexcept = default;
        constexpr explicit TContainerRegistryIndex(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TContainerRegistryIndex invalid() noexcept { return TContainerRegistryIndex{k_invalid_value}; }
        [[nodiscard]] static constexpr TContainerRegistryIndex from_raw(value_type input) noexcept { return TContainerRegistryIndex{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TContainerRegistryIndex lhs, TContainerRegistryIndex rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TContainerRegistryIndex lhs, TContainerRegistryIndex rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TContainerRegistryIndex> {
        std::size_t operator()(const assembler::circulation_mechanism::TContainerRegistryIndex& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TContainerRegistryIndex::value_type>{}(input.raw());
        }
    };
    }

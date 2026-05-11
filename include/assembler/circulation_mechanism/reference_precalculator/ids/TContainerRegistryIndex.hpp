#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TContainerRegistryIndex.hpp

        Delivery:
            CME-REFPREC-PROD-W01 — Production Locating And Ref Supply Contract

        Current responsibility:
            One-based container registry locator used by waiting-list candidates.

        Production capabilities:
            - typed identity/locator atom.
            - invalid()/from_raw()/raw()/is_valid().
            - equality/inequality.
            - hash specialization.
            - one-based / zero-based helpers.

        Explicit non-ownership:
            - Does not own containers or slots.
            - Does not execute ingress or dispatch.
            - Does not own bridge/receiver lifecycle.
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

        [[nodiscard]] constexpr value_type one_based() const noexcept { return value; }
        [[nodiscard]] constexpr value_type zero_based_or(value_type fallback) const noexcept { return is_valid() ? value - 1U : fallback; }

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

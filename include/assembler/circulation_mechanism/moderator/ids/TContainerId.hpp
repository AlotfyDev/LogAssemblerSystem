#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TContainerId.hpp

        Delivery:
            CME-MODERATOR-PROD-W01 — Production Reset And Readiness Contract

        Current responsibility:
            Identifies a moderated container.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not own container storage.
            - Does not own bundle topology.
            - Does not execute registry rebuild.
            - Does not calculate access references.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TContainerId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TContainerId() noexcept = default;
        constexpr explicit TContainerId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TContainerId invalid() noexcept { return TContainerId{k_invalid_value}; }
        [[nodiscard]] static constexpr TContainerId from_raw(value_type input) noexcept { return TContainerId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TContainerId lhs, TContainerId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TContainerId lhs, TContainerId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TContainerId> {
        std::size_t operator()(const assembler::circulation_mechanism::TContainerId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TContainerId::value_type>{}(input.raw());
        }
    };
    }

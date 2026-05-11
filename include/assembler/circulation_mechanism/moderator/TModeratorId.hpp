#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TModeratorId.hpp

        Delivery:
            CME-MODERATOR-PROD-W01 — Production Reset And Readiness Contract

        Current responsibility:
            Identifies a SlotsContainerModerator instance.

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

    struct TModeratorId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TModeratorId() noexcept = default;
        constexpr explicit TModeratorId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TModeratorId invalid() noexcept { return TModeratorId{k_invalid_value}; }
        [[nodiscard]] static constexpr TModeratorId from_raw(value_type input) noexcept { return TModeratorId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TModeratorId lhs, TModeratorId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TModeratorId lhs, TModeratorId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TModeratorId> {
        std::size_t operator()(const assembler::circulation_mechanism::TModeratorId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TModeratorId::value_type>{}(input.raw());
        }
    };
    }

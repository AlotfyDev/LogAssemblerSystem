#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideProfileId.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Current responsibility:
            Identifies one read-side/post-bridge circulation profile.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute bridge runtime.
            - Does not execute receiver/addon behavior.
            - Does not persist payload.
            - Does not mutate pre-bridge CME state.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TReadSideProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideProfileId() noexcept = default;
        constexpr explicit TReadSideProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideProfileId invalid() noexcept { return TReadSideProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideProfileId from_raw(value_type input) noexcept { return TReadSideProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideProfileId lhs, TReadSideProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideProfileId lhs, TReadSideProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileId::value_type>{}(input.raw());
        }
    };
    }

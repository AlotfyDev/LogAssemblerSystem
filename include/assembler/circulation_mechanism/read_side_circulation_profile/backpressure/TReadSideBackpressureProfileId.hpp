#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideBackpressureProfileId.hpp

        Delivery:
            CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile

        Current responsibility:
            Identifies one read-side backpressure profile.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute backpressure algorithms.
            - Does not release payload.
            - Does not call receiver.
            - Does not execute persistence.
            - Does not mutate pre-bridge CME state.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TReadSideBackpressureProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideBackpressureProfileId() noexcept = default;
        constexpr explicit TReadSideBackpressureProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideBackpressureProfileId invalid() noexcept { return TReadSideBackpressureProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideBackpressureProfileId from_raw(value_type input) noexcept { return TReadSideBackpressureProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideBackpressureProfileId lhs, TReadSideBackpressureProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideBackpressureProfileId lhs, TReadSideBackpressureProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideBackpressureProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideBackpressureProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideBackpressureProfileId::value_type>{}(input.raw());
        }
    };
    }

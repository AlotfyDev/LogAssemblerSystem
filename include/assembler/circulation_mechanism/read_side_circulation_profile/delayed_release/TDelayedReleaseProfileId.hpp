#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TDelayedReleaseProfileId.hpp

        Delivery:
            CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile

        Current responsibility:
            Identifies one delayed-release profile.

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

    struct TDelayedReleaseProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TDelayedReleaseProfileId() noexcept = default;
        constexpr explicit TDelayedReleaseProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TDelayedReleaseProfileId invalid() noexcept { return TDelayedReleaseProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TDelayedReleaseProfileId from_raw(value_type input) noexcept { return TDelayedReleaseProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TDelayedReleaseProfileId lhs, TDelayedReleaseProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TDelayedReleaseProfileId lhs, TDelayedReleaseProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TDelayedReleaseProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TDelayedReleaseProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TDelayedReleaseProfileId::value_type>{}(input.raw());
        }
    };
    }

#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideCapacityReportId.hpp

        Delivery:
            CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile

        Current responsibility:
            Identifies one read-side capacity/backpressure/delayed-release report.

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

    struct TReadSideCapacityReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideCapacityReportId() noexcept = default;
        constexpr explicit TReadSideCapacityReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideCapacityReportId invalid() noexcept { return TReadSideCapacityReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideCapacityReportId from_raw(value_type input) noexcept { return TReadSideCapacityReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideCapacityReportId lhs, TReadSideCapacityReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideCapacityReportId lhs, TReadSideCapacityReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideCapacityReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideCapacityReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideCapacityReportId::value_type>{}(input.raw());
        }
    };
    }

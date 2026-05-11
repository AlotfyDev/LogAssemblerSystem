#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideProfileReportId.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Current responsibility:
            Identifies one read-side profile readiness report.

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

    struct TReadSideProfileReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideProfileReportId() noexcept = default;
        constexpr explicit TReadSideProfileReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideProfileReportId invalid() noexcept { return TReadSideProfileReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideProfileReportId from_raw(value_type input) noexcept { return TReadSideProfileReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideProfileReportId lhs, TReadSideProfileReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideProfileReportId lhs, TReadSideProfileReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideProfileReportId::value_type>{}(input.raw());
        }
    };
    }

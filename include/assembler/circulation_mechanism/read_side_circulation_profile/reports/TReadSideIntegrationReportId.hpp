#pragma once

    #include <cstdint>
    #include <functional>

    /*
        TReadSideIntegrationReportId.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Current responsibility:
            Identifies one read-side integration report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not invoke addon runtime.
            - Does not persist payload.
            - Does not export telemetry.
            - Does not execute bridge or receiver behavior.
            - Does not recover failed dispatch.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TReadSideIntegrationReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;

        value_type value{k_invalid_value};

        constexpr TReadSideIntegrationReportId() noexcept = default;
        constexpr explicit TReadSideIntegrationReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideIntegrationReportId invalid() noexcept { return TReadSideIntegrationReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideIntegrationReportId from_raw(value_type input) noexcept { return TReadSideIntegrationReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideIntegrationReportId lhs, TReadSideIntegrationReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideIntegrationReportId lhs, TReadSideIntegrationReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideIntegrationReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideIntegrationReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideIntegrationReportId::value_type>{}(input.raw());
        }
    };
    }

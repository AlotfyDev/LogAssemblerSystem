#pragma once

    #include <cstdint>
    #include <functional>

    /*
        TReadSideDiagnosticId.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Current responsibility:
            Identifies one read-side diagnostic record.

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

    struct TReadSideDiagnosticId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;

        value_type value{k_invalid_value};

        constexpr TReadSideDiagnosticId() noexcept = default;
        constexpr explicit TReadSideDiagnosticId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideDiagnosticId invalid() noexcept { return TReadSideDiagnosticId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideDiagnosticId from_raw(value_type input) noexcept { return TReadSideDiagnosticId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideDiagnosticId lhs, TReadSideDiagnosticId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideDiagnosticId lhs, TReadSideDiagnosticId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideDiagnosticId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side_circulation_profile::TReadSideDiagnosticId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side_circulation_profile::TReadSideDiagnosticId::value_type>{}(input.raw());
        }
    };
    }

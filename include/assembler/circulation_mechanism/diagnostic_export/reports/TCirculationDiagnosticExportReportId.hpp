#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationDiagnosticExportReportId.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Current responsibility:
            Identifies one diagnostic export report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not export telemetry.
            - Does not write files.
            - Does not persist records.
            - Does not execute recovery.
            - Does not mutate PreBridge/ReadSide runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    struct TCirculationDiagnosticExportReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationDiagnosticExportReportId() noexcept = default;
        constexpr explicit TCirculationDiagnosticExportReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationDiagnosticExportReportId invalid() noexcept { return TCirculationDiagnosticExportReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationDiagnosticExportReportId from_raw(value_type input) noexcept { return TCirculationDiagnosticExportReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationDiagnosticExportReportId lhs, TCirculationDiagnosticExportReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationDiagnosticExportReportId lhs, TCirculationDiagnosticExportReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportReportId::value_type>{}(input.raw());
        }
    };
    }

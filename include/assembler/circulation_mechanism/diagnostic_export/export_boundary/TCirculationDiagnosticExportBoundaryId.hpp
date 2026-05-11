#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationDiagnosticExportBoundaryId.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Current responsibility:
            Identifies one diagnostic export boundary.

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

    struct TCirculationDiagnosticExportBoundaryId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationDiagnosticExportBoundaryId() noexcept = default;
        constexpr explicit TCirculationDiagnosticExportBoundaryId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationDiagnosticExportBoundaryId invalid() noexcept { return TCirculationDiagnosticExportBoundaryId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationDiagnosticExportBoundaryId from_raw(value_type input) noexcept { return TCirculationDiagnosticExportBoundaryId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationDiagnosticExportBoundaryId lhs, TCirculationDiagnosticExportBoundaryId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationDiagnosticExportBoundaryId lhs, TCirculationDiagnosticExportBoundaryId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportBoundaryId> {
        std::size_t operator()(const assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportBoundaryId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::diagnostic_export::TCirculationDiagnosticExportBoundaryId::value_type>{}(input.raw());
        }
    };
    }

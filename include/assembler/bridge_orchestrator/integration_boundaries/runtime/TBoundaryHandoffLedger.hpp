#pragma once
#include <array>
#include <cstddef>
#include "assembler/communication_context/integration_boundaries/runtime/TBoundaryHandoffRuntimeReport.hpp"

/**
 * @file TBoundaryHandoffLedger.hpp
 * @brief Bounded in-memory ledger for boundary handoff runtime reports.
 */
namespace assembler::communication_context {
    template <std::size_t Capacity>
    struct TBoundaryHandoffLedger final {
        std::array<TBoundaryHandoffRuntimeReport, Capacity> reports{};
        std::size_t count{0u};
        std::uint64_t rejected_reports{0u};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity; }
        constexpr bool add(TBoundaryHandoffRuntimeReport report) noexcept {
            if (count >= Capacity || !report.is_valid()) { ++rejected_reports; return false; }
            reports[count++] = report;
            return true;
        }
    };
}

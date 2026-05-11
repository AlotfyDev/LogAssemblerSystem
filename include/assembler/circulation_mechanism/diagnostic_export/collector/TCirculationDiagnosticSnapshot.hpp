#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "TCirculationDiagnosticRecord.hpp"

/*
    TCirculationDiagnosticSnapshot.hpp

    Current responsibility:
        Fixed-size diagnostic snapshot emitted by the unified collector.

    Non-ownership:
        Snapshot is read-only evidence; it is not an exporter or recovery mechanism.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

template <std::size_t Capacity>
struct TCirculationDiagnosticSnapshot final {
    std::array<TCirculationDiagnosticRecord, Capacity> records{};
    std::uint32_t count{0};
    TCirculationDiagnosticSeverity highest_severity{TCirculationDiagnosticSeverity::trace};
    bool has_blocking_issue{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return count <= Capacity;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return count == 0U;
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler

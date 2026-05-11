#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "TCirculationDiagnosticCollectorId.hpp"
#include "TCirculationDiagnosticSnapshot.hpp"

/*
    TCirculationDiagnosticCollector.hpp

    Delivery:
        CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

    Current responsibility:
        Allocation-free fixed-capacity diagnostic collector.

    Production capabilities:
        - accepts records
        - counts records
        - tracks highest severity
        - tracks blocking issue
        - produces read-only snapshot
        - rejects overflow without allocation

    Explicit non-ownership:
        - Does not log/export records.
        - Does not execute recovery.
        - Does not mutate source systems.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

template <std::size_t Capacity>
class TCirculationDiagnosticCollector final {
public:
    static_assert(Capacity > 0U, "Diagnostic collector capacity must be greater than zero.");

    constexpr explicit TCirculationDiagnosticCollector(TCirculationDiagnosticCollectorId id) noexcept
        : id_(id)
    {
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid();
    }

    [[nodiscard]] constexpr std::uint32_t size() const noexcept {
        return count_;
    }

    [[nodiscard]] constexpr bool full() const noexcept {
        return count_ >= Capacity;
    }

    constexpr bool accept(TCirculationDiagnosticRecord record) noexcept {
        if (!is_valid() || !record.has_issue() || full()) {
            return false;
        }
        record.sequence = ++sequence_;
        records_[count_++] = record;
        if (static_cast<std::uint8_t>(record.severity) > static_cast<std::uint8_t>(highest_)) {
            highest_ = record.severity;
        }
        if (record.blocks_readiness()) {
            blocking_ = true;
        }
        return true;
    }

    [[nodiscard]] constexpr TCirculationDiagnosticSnapshot<Capacity> snapshot() const noexcept {
        return TCirculationDiagnosticSnapshot<Capacity>{records_, count_, highest_, blocking_};
    }

private:
    TCirculationDiagnosticCollectorId id_{TCirculationDiagnosticCollectorId::invalid()};
    std::array<TCirculationDiagnosticRecord, Capacity> records_{};
    std::uint32_t count_{0};
    std::uint64_t sequence_{0};
    TCirculationDiagnosticSeverity highest_{TCirculationDiagnosticSeverity::trace};
    bool blocking_{false};
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler

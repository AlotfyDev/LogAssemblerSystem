#pragma once
#include "TDispatchReportId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatcherId.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TBoundaryAssumptionBrokenReport final {
    TDispatchReportId report_id{};
    TDispatcherId dispatcher_id{};
    bool bridge_drain_assumption_broken{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && dispatcher_id.is_valid(); }
    [[nodiscard]] constexpr bool is_broken() const noexcept { return bridge_drain_assumption_broken; }
};
} // namespace circulation_mechanism
} // namespace assembler

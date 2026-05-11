#pragma once
#include "TDispatchReportId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatcherId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatchExposureStatus.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatchExecutionStatus.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TDispatchAccessRef.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchExposureReport final {
    TDispatchReportId report_id{};
    TDispatcherId dispatcher_id{};
    TDispatchAccessRef dispatch_ref{};
    TDispatchExposureStatus exposure_status{TDispatchExposureStatus::not_exposed};
    TDispatchExecutionStatus execution_status{TDispatchExecutionStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && dispatcher_id.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return execution_status == TDispatchExecutionStatus::accepted; }
    [[nodiscard]] constexpr bool exposed() const noexcept { return accepted() && exposure_status == TDispatchExposureStatus::exposed; }
};
} // namespace circulation_mechanism
} // namespace assembler

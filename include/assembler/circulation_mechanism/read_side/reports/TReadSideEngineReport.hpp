#pragma once
#include "TReadSideEngineReportId.hpp"
#include "TReadSideEngineIssueKind.hpp"
#include "../TReadSideEngineId.hpp"
#include "../runtime/TReadSideRuntimeState.hpp"

/*
    TReadSideEngineReport.hpp

    Current responsibility:
        Evidence report for ReadSide engine configuration/lifecycle.

    Non-ownership:
        Report does not execute runtime.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideEngineReport final {
    TReadSideEngineReportId report_id{};
    TReadSideEngineId engine_id{};
    TReadSideRuntimeState before{TReadSideRuntimeState::unconfigured};
    TReadSideRuntimeState after{TReadSideRuntimeState::unconfigured};
    TReadSideEngineIssueKind issue{TReadSideEngineIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && engine_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && issue == TReadSideEngineIssueKind::none; }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

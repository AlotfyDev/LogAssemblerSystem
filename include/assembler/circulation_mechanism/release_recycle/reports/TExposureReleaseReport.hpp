#pragma once
#include "TReleaseRecycleReportId.hpp"
#include "assembler/circulation_mechanism/state/TDispatchExposureState.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleStatus.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TExposureReleaseReport final {
    TReleaseRecycleReportId report_id{};
    TDispatchExposureState before{TDispatchExposureState::passive_exposed};
    TDispatchExposureState after{TDispatchExposureState::closed};
    TReleaseRecycleStatus status{TReleaseRecycleStatus::not_attempted};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
    [[nodiscard]] constexpr bool released() const noexcept {
        return status == TReleaseRecycleStatus::accepted && after == TDispatchExposureState::closed;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

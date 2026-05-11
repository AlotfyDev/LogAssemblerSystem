#pragma once
#include "TReleaseRecycleReportId.hpp"
#include "assembler/circulation_mechanism/ids/TReferenceId.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleStatus.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TReferenceReleaseReport final {
    TReleaseRecycleReportId report_id{};
    TReferenceId reference_id{};
    TReferenceValidityState before{TReferenceValidityState::issued};
    TReferenceValidityState after{TReferenceValidityState::invalidated};
    TReleaseRecycleStatus status{TReleaseRecycleStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && reference_id.is_valid(); }
    [[nodiscard]] constexpr bool released() const noexcept { return status == TReleaseRecycleStatus::accepted && reference_released(after); }
};
} // namespace circulation_mechanism
} // namespace assembler

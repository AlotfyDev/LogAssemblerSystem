#pragma once
#include "TReleaseRecycleReportId.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleId.hpp"
#include "assembler/circulation_mechanism/release_recycle/TRecycleState.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleStatus.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TRecycleReport final {
    TReleaseRecycleReportId report_id{};
    TReleaseRecycleId recycle_id{};
    TRecycleState before{TRecycleState::not_recyclable};
    TRecycleState after{TRecycleState::not_recyclable};
    TReleaseRecycleStatus status{TReleaseRecycleStatus::not_attempted};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && recycle_id.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TReleaseRecycleStatus::accepted; }
    [[nodiscard]] constexpr bool changed() const noexcept { return before != after; }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "TReleaseRecycleReportId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleStatus.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TResetAppliedReport final {
    TReleaseRecycleReportId report_id{};
    TContainerId container_id{};
    TContainerState before{TContainerState::reset_pending};
    TContainerState after{TContainerState::default_empty};
    TReleaseRecycleStatus status{TReleaseRecycleStatus::not_attempted};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && container_id.is_valid(); }
    [[nodiscard]] constexpr bool reset_to_default_empty() const noexcept {
        return status == TReleaseRecycleStatus::accepted && after == TContainerState::default_empty;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

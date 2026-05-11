#pragma once
#include "TReleaseRecycleId.hpp"
#include "TReleaseKind.hpp"
#include "TRecycleState.hpp"
#include "TReleaseRecycleStatus.hpp"
#include "assembler/circulation_mechanism/state/TReleaseRecycleStateHelpers.hpp"

/*
    TReleaseRecycleRecord.hpp

    Responsibility:
        Runtime record for release/recycle lifecycle progression.
*/
namespace assembler {
namespace circulation_mechanism {

struct TReleaseRecycleRecord final {
    TReleaseRecycleId id{};
    TReleaseKind kind{TReleaseKind::container_release};
    TRecycleState state{TRecycleState::not_recyclable};
    bool active_references_cleared{false};
    bool exposure_closed{false};
    bool safe_point_confirmed{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

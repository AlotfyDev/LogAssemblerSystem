#pragma once
#include "TRoundKind.hpp"
#include "TRoundLifecycleStatus.hpp"
#include "assembler/circulation_mechanism/ids/TRoundId.hpp"
#include "assembler/circulation_mechanism/state/TRoundState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TRoundClosureReport final {
    TRoundId round_id{};
    TRoundKind kind{TRoundKind::ingress};
    TRoundState before{TRoundState::idle};
    TRoundState after{TRoundState::idle};
    TRoundLifecycleStatus status{TRoundLifecycleStatus::not_attempted};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return round_id.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TRoundLifecycleStatus::accepted; }
    [[nodiscard]] constexpr bool closed() const noexcept { return accepted() && (after == TRoundState::closed || after == TRoundState::completed); }
};
} // namespace circulation_mechanism
} // namespace assembler

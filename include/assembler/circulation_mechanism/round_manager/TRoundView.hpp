#pragma once
#include <cstdint>
#include "TRoundKind.hpp"
#include "assembler/circulation_mechanism/ids/TRoundId.hpp"
#include "assembler/circulation_mechanism/state/TRoundState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TRoundView final {
    TRoundId round_id{};
    TRoundKind kind{TRoundKind::ingress};
    TRoundState state{TRoundState::idle};
    std::uint32_t member_count{0};
    std::uint32_t member_capacity{0};
    std::uint64_t generation{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return round_id.is_valid() && member_capacity > 0U && member_count <= member_capacity && generation > 0U;
    }
    [[nodiscard]] constexpr bool accepts_candidates() const noexcept { return round_accepts_candidates(state); }
    [[nodiscard]] constexpr bool membership_fixed() const noexcept { return round_membership_fixed(state); }
};
} // namespace circulation_mechanism
} // namespace assembler

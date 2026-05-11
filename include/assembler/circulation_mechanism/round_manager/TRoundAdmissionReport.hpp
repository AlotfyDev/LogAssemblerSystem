#pragma once
#include "TRoundKind.hpp"
#include "TRoundAdmissionDecisionKind.hpp"
#include "assembler/circulation_mechanism/ids/TRoundId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TRoundAdmissionReport final {
    TRoundId round_id{};
    TRoundKind kind{TRoundKind::ingress};
    TContainerRegistryIndex candidate_index{};
    TRoundAdmissionDecisionKind decision{TRoundAdmissionDecisionKind::rejected_invalid_round};
    std::uint32_t member_count_after{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return round_id.is_valid() && candidate_index.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return decision == TRoundAdmissionDecisionKind::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

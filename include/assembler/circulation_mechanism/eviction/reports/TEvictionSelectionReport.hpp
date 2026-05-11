#pragma once
#include "TEvictionReportId.hpp"
#include "TEvictionReportKind.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionPolicyKind.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEvictionSelectionReport final {
    TEvictionReportId report_id{};
    TEvictionReportKind report_kind{TEvictionReportKind::selection};
    TEvictionPolicyKind policy_kind{TEvictionPolicyKind::no_eviction_pre_bridge};
    TEvictionCandidate candidate{};
    TEvictionEvaluationStatus evaluation{TEvictionEvaluationStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && candidate.is_valid(); }
    [[nodiscard]] constexpr bool selected() const noexcept { return evaluation == TEvictionEvaluationStatus::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

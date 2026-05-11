#pragma once
#include "TEvictionReportId.hpp"
#include "TEvictionReportKind.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEvictionRejectedReport final {
    TEvictionReportId report_id{};
    TEvictionReportKind report_kind{TEvictionReportKind::rejected};
    TEvictionCandidate candidate{};
    TEvictionEvaluationStatus evaluation{TEvictionEvaluationStatus::not_attempted};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && candidate.is_valid(); }
    [[nodiscard]] constexpr bool rejected() const noexcept { return evaluation != TEvictionEvaluationStatus::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

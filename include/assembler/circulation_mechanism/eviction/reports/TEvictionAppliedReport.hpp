#pragma once
#include "TEvictionReportId.hpp"
#include "TEvictionReportKind.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEvictionAppliedReport final {
    TEvictionReportId report_id{};
    TEvictionReportKind report_kind{TEvictionReportKind::applied};
    TEvictionCandidate candidate{};
    bool applied{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && candidate.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

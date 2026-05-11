#pragma once
#include "TEvictionReportId.hpp"
#include "TEvictionReportKind.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionPolicyKind.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TCapacityDelegatedToReadSideReport final {
    TEvictionReportId report_id{};
    TEvictionReportKind report_kind{TEvictionReportKind::delegated};
    TEvictionPolicyKind policy_kind{TEvictionPolicyKind::delegate_to_read_side};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

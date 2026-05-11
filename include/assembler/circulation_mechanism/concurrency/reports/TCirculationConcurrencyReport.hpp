#pragma once
#include "TCirculationConcurrencyReportId.hpp"
#include "../TCirculationConcurrencyIssueKind.hpp"
#include "../TCirculationConcurrencyMode.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TCirculationConcurrencyReport final {
    TCirculationConcurrencyReportId report_id{};
    TCirculationConcurrencyMode mode{TCirculationConcurrencyMode::single_writer_independent_instances};
    TCirculationConcurrencyIssueKind issue{TCirculationConcurrencyIssueKind::none};
    bool accepted{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && accepted && issue == TCirculationConcurrencyIssueKind::none; }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

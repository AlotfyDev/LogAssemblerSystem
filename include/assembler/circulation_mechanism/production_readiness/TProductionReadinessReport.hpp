#pragma once

#include "TProductionReadinessGateId.hpp"
#include "TProductionReadinessStatus.hpp"
#include "TProductionReadinessIssueKind.hpp"
#include "TProductionReadinessSeverity.hpp"

/*
    TProductionReadinessReport.hpp

    Responsibility:
        Reports the outcome of a production readiness gate evaluation.

    Non-ownership:
        Report is evidence. It does not run or certify external systems.
*/

namespace assembler {
namespace circulation_mechanism {

struct TProductionReadinessReport final {
    TProductionReadinessGateId gate_id{};
    TProductionReadinessStatus status{TProductionReadinessStatus::not_evaluated};
    TProductionReadinessIssueKind issue{TProductionReadinessIssueKind::none};
    TProductionReadinessSeverity severity{TProductionReadinessSeverity::info};
    std::uint32_t required_count{0};
    std::uint32_t passed_required_count{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return gate_id.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid()
            && status == TProductionReadinessStatus::passed
            && issue == TProductionReadinessIssueKind::none
            && required_count == passed_required_count;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

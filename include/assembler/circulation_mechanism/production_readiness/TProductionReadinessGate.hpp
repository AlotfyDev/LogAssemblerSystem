#pragma once

#include "TProductionReadinessCriterion.hpp"
#include "TProductionReadinessReport.hpp"

/*
    TProductionReadinessGate.hpp

    Delivery:
        CME-INTEGRATION-PROD-W04 — Production Readiness Gate

    Current responsibility:
        Evaluates fixed-size production readiness criteria.

    Production capabilities:
        - checks required criteria,
        - blocks on missing evidence,
        - blocks on failed compile/test/anti-collapse/gap closure evidence,
        - produces readiness report,
        - remains pure/evidence-driven.

    Explicit non-ownership:
        - Does not run the tests itself.
        - Does not mutate components.
        - Does not execute bridge or receiver runtime.
        - Does not override failed evidence.
*/

namespace assembler {
namespace circulation_mechanism {

template <std::size_t CriterionCount>
class TProductionReadinessGate final {
public:
    constexpr TProductionReadinessGate(TProductionReadinessGateId gate_id, const std::array<TProductionReadinessCriterion, CriterionCount>& criteria) noexcept
        : gate_id_(gate_id), criteria_(criteria)
    {
    }

    [[nodiscard]] constexpr TProductionReadinessReport evaluate() const noexcept {
        if (!gate_id_.is_valid()) {
            return TProductionReadinessReport{gate_id_, TProductionReadinessStatus::failed, TProductionReadinessIssueKind::missing_gate_id, TProductionReadinessSeverity::critical, 0U, 0U};
        }

        std::uint32_t required_count = 0U;
        std::uint32_t passed_count = 0U;

        for (const auto& criterion : criteria_) {
            if (!criterion.required) {
                continue;
            }

            ++required_count;

            if (!criterion.evidence.present) {
                return TProductionReadinessReport{gate_id_, TProductionReadinessStatus::failed, TProductionReadinessIssueKind::missing_evidence, TProductionReadinessSeverity::critical, required_count, passed_count};
            }

            if (!criterion.evidence.passed) {
                return TProductionReadinessReport{gate_id_, TProductionReadinessStatus::failed, criterion.evidence.issue, criterion.evidence.severity, required_count, passed_count};
            }

            if (criterion.evidence.issue != TProductionReadinessIssueKind::none) {
                return TProductionReadinessReport{gate_id_, TProductionReadinessStatus::failed, criterion.evidence.issue, criterion.evidence.severity, required_count, passed_count};
            }

            ++passed_count;
        }

        return TProductionReadinessReport{gate_id_, TProductionReadinessStatus::passed, TProductionReadinessIssueKind::none, TProductionReadinessSeverity::info, required_count, passed_count};
    }

private:
    TProductionReadinessGateId gate_id_{};
    std::array<TProductionReadinessCriterion, CriterionCount> criteria_{};
};
} // namespace circulation_mechanism
} // namespace assembler

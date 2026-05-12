#pragma once
#include <array>
#include "TCirculationProductionReadinessGateId.hpp"
#include "criteria/TCirculationProductionReadinessCriterion.hpp"
#include "reports/TCirculationProductionReadinessReport.hpp"

/*
    TCirculationProductionReadinessGate.hpp

    Delivery:
        CME-PROD-HARDEN-W08 — Final Production Readiness Gate

    Current responsibility:
        Evaluates final production readiness evidence.

    Production capabilities:
        - evaluates fixed-size criteria set
        - fails on missing evidence
        - fails on failed required evidence
        - counts deferred optional evidence
        - produces final readiness report

    Explicit non-ownership:
        - Does not run tests itself.
        - Does not deploy.
        - Does not mutate components.
        - Does not certify external bridge/receiver/addon implementations.
*/
namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

template <std::size_t CriterionCount>
class TCirculationProductionReadinessGate final {
public:
    constexpr TCirculationProductionReadinessGate(
        TCirculationProductionReadinessGateId gate_id,
        TCirculationProductionReadinessReportId report_id,
        const std::array<TCirculationProductionReadinessCriterion, CriterionCount>& criteria) noexcept
        : gate_id_(gate_id),
          report_id_(report_id),
          criteria_(criteria)
    {
    }

    [[nodiscard]] constexpr TCirculationProductionReadinessReport evaluate() const noexcept {
        if (!gate_id_.is_valid()) {
            return TCirculationProductionReadinessReport{
                report_id_,
                TCirculationProductionReadinessStatus::failed,
                TCirculationProductionReadinessIssueKind::missing_gate_id,
                TCirculationProductionReadinessSeverity::critical,
                0U,
                0U,
                0U
            };
        }

        std::uint32_t required_count = 0U;
        std::uint32_t passed_count = 0U;
        std::uint32_t deferred_count = 0U;

        for (const auto& criterion : criteria_) {
            if (!criterion.required) {
                if (!criterion.evidence.present || !criterion.evidence.passed) {
                    ++deferred_count;
                }
                continue;
            }

            ++required_count;

            if (!criterion.evidence.present) {
                return TCirculationProductionReadinessReport{
                    report_id_,
                    TCirculationProductionReadinessStatus::failed,
                    TCirculationProductionReadinessIssueKind::missing_evidence,
                    TCirculationProductionReadinessSeverity::critical,
                    required_count,
                    passed_count,
                    deferred_count
                };
            }

            if (!criterion.evidence.passed || criterion.evidence.issue != TCirculationProductionReadinessIssueKind::none) {
                return TCirculationProductionReadinessReport{
                    report_id_,
                    TCirculationProductionReadinessStatus::failed,
                    criterion.evidence.issue == TCirculationProductionReadinessIssueKind::none
                        ? TCirculationProductionReadinessIssueKind::criterion_failed
                        : criterion.evidence.issue,
                    criterion.evidence.severity,
                    required_count,
                    passed_count,
                    deferred_count
                };
            }

            ++passed_count;
        }

        return TCirculationProductionReadinessReport{
            report_id_,
            TCirculationProductionReadinessStatus::passed,
            TCirculationProductionReadinessIssueKind::none,
            TCirculationProductionReadinessSeverity::info,
            required_count,
            passed_count,
            deferred_count
        };
    }

private:
    TCirculationProductionReadinessGateId gate_id_{};
    TCirculationProductionReadinessReportId report_id_{};
    std::array<TCirculationProductionReadinessCriterion, CriterionCount> criteria_{};
};
} // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

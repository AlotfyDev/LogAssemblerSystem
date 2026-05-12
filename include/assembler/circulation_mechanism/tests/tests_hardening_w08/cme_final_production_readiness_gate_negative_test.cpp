#include "assembler/circulation_mechanism/circulation_mechanism_final_readiness.hpp"

#include <array>

using namespace assembler::circulation_mechanism::final_readiness;

int main()
{
    constexpr std::array<TCirculationProductionReadinessCriterion, 1> missing{
        TCirculationProductionReadinessCriterion{
            TCirculationProductionReadinessCriterionKind::gap_closure_complete,
            true,
            TCirculationProductionReadinessEvidenceRef{
                TCirculationProductionReadinessCriterionKind::gap_closure_complete,
                false,
                false,
                TCirculationProductionReadinessIssueKind::missing_evidence,
                TCirculationProductionReadinessSeverity::critical
            }
        }
    };

    constexpr TCirculationProductionReadinessGate<missing.size()> gate{
        TCirculationProductionReadinessGateId::from_raw(1),
        TCirculationProductionReadinessReportId::from_raw(2),
        missing
    };

    constexpr auto report = gate.evaluate();
    static_assert(!report.passed(), "missing evidence fails gate");
    static_assert(report.issue == TCirculationProductionReadinessIssueKind::missing_evidence, "missing evidence issue");

    constexpr std::array<TCirculationProductionReadinessCriterion, 1> failed{
        TCirculationProductionReadinessCriterion{
            TCirculationProductionReadinessCriterionKind::build_ci_ready,
            true,
            TCirculationProductionReadinessEvidenceRef{
                TCirculationProductionReadinessCriterionKind::build_ci_ready,
                true,
                false,
                TCirculationProductionReadinessIssueKind::build_ci_failed,
                TCirculationProductionReadinessSeverity::critical
            }
        }
    };

    constexpr TCirculationProductionReadinessGate<failed.size()> failed_gate{
        TCirculationProductionReadinessGateId::from_raw(3),
        TCirculationProductionReadinessReportId::from_raw(4),
        failed
    };

    constexpr auto failed_report = failed_gate.evaluate();
    static_assert(!failed_report.passed(), "failed evidence fails gate");
    static_assert(failed_report.issue == TCirculationProductionReadinessIssueKind::build_ci_failed, "build ci issue");

    return 0;
}

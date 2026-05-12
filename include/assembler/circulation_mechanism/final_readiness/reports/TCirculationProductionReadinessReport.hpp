#pragma once
#include "TCirculationProductionReadinessReportId.hpp"
#include "../TCirculationProductionReadinessStatus.hpp"
#include "../TCirculationProductionReadinessIssueKind.hpp"
#include "../TCirculationProductionReadinessSeverity.hpp"

/*
    TCirculationProductionReadinessReport.hpp

    Current responsibility:
        Final evidence report for production readiness.

    Non-ownership:
        Does not deploy, run, or mutate the engine.
*/
namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

struct TCirculationProductionReadinessReport final {
    TCirculationProductionReadinessReportId report_id{};
    TCirculationProductionReadinessStatus status{TCirculationProductionReadinessStatus::not_evaluated};
    TCirculationProductionReadinessIssueKind issue{TCirculationProductionReadinessIssueKind::none};
    TCirculationProductionReadinessSeverity severity{TCirculationProductionReadinessSeverity::info};
    std::uint32_t required_count{0};
    std::uint32_t passed_required_count{0};
    std::uint32_t deferred_count{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return report_id.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid()
            && status == TCirculationProductionReadinessStatus::passed
            && issue == TCirculationProductionReadinessIssueKind::none
            && required_count == passed_required_count;
    }
};
} // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

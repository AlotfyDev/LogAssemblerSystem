#pragma once

#include "TReadSideIntegrationReportId.hpp"
#include "TReadSideIntegrationIssueKind.hpp"
#include "TReadSideIntegrationDecisionKind.hpp"
#include "../diagnostics/TReadSideDiagnosticRecord.hpp"
#include "../addon_boundary/TAddonBoundaryDescriptor.hpp"

    /*
        TReadSideIntegrationReport.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Current responsibility:
            Production evidence for read-side diagnostic/addon integration readiness.

        Production capabilities:
            - combines diagnostic and addon-boundary state,
            - evaluates readiness,
            - distinguishes ready, blocked, deferred, diagnostic-only, and manual-review states,
            - reports integration issue kind.

        Non-ownership:
            - Does not execute addon runtime.
            - Does not persist/export data.
            - Does not recover failed dispatch.
    */
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideIntegrationReport final {
    TReadSideIntegrationReportId report_id{};
    TReadSideDiagnosticRecord diagnostic{};
    TAddonBoundaryDescriptor addon_boundary{};
    TReadSideIntegrationIssueKind issue{TReadSideIntegrationIssueKind::none};
    TReadSideIntegrationDecisionKind decision{TReadSideIntegrationDecisionKind::ready};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return report_id.is_valid() && addon_boundary.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid()
            && issue == TReadSideIntegrationIssueKind::none
            && decision == TReadSideIntegrationDecisionKind::ready
            && addon_boundary.ready()
            && !diagnostic.blocks_integration();
    }

    [[nodiscard]] static constexpr TReadSideIntegrationReport evaluate(
        TReadSideIntegrationReportId report_id,
        TReadSideDiagnosticRecord diagnostic,
        TAddonBoundaryDescriptor addon) noexcept
    {
        if (!addon.is_valid()) {
            return TReadSideIntegrationReport{
                report_id,
                diagnostic,
                addon,
                TReadSideIntegrationIssueKind::missing_addon_boundary,
                TReadSideIntegrationDecisionKind::blocked
            };
        }

        if (diagnostic.blocks_integration()) {
            return TReadSideIntegrationReport{
                report_id,
                diagnostic,
                addon,
                TReadSideIntegrationIssueKind::diagnostic_issue_present,
                TReadSideIntegrationDecisionKind::blocked
            };
        }

        if (addon.deferred_or_diagnostic_only()) {
            return TReadSideIntegrationReport{
                report_id,
                diagnostic,
                addon,
                TReadSideIntegrationIssueKind::none,
                TReadSideIntegrationDecisionKind::diagnostic_only
            };
        }

        if (!addon.ready()) {
            return TReadSideIntegrationReport{
                report_id,
                diagnostic,
                addon,
                TReadSideIntegrationIssueKind::addon_not_ready,
                TReadSideIntegrationDecisionKind::blocked
            };
        }

        return TReadSideIntegrationReport{
            report_id,
            diagnostic,
            addon,
            TReadSideIntegrationIssueKind::none,
            TReadSideIntegrationDecisionKind::ready
        };
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

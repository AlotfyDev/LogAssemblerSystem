#include <cassert>
#include <iostream>

#include "assembler/log_level_api/diagnostics/TLogApiDiagnosticsSurface.hpp"

int main() {
    using namespace assembler::log_level_api::diagnostics;

    auto config = TLogApiDiagnosticFactory::Make(
        1,
        TLogApiDiagnosticSeverity::Error,
        TLogApiFailureKind::ConfigurationNotReady,
        "api_configurator",
        "LOGAPI_CFG_NOT_READY",
        "Configuration is not ready.",
        true
    );

    auto content = TLogApiDiagnosticFactory::Make(
        2,
        TLogApiDiagnosticSeverity::Warning,
        TLogApiFailureKind::ContentMissing,
        "api_facade",
        "LOGAPI_CONTENT_MISSING",
        "Content is missing.",
        false
    );

    auto handoff = TLogApiDiagnosticFactory::Make(
        3,
        TLogApiDiagnosticSeverity::Error,
        TLogApiFailureKind::HandoffContractRejected,
        "communication_bindings",
        "LOGAPI_HANDOFF_REJECTED",
        "Handoff contract rejected the request.",
        true
    );

    assert(config.IsPresent());
    assert(config.category == TLogApiDiagnosticCategory::Configuration);
    assert(config.boundary == TLogApiFailureBoundaryKind::ConfigurationSurface);

    assert(content.IsPresent());
    assert(content.category == TLogApiDiagnosticCategory::ContentInput);
    assert(content.boundary == TLogApiFailureBoundaryKind::UpstreamCallerInput);

    assert(handoff.IsPresent());
    assert(handoff.category == TLogApiDiagnosticCategory::CirculationHandoff);
    assert(handoff.boundary == TLogApiFailureBoundaryKind::CirculationBoundary);

    TLogApiDiagnosticCollector collector{};
    collector.Add(config);
    collector.Add(content);
    collector.Add(handoff);

    const auto& report = collector.Report();
    assert(report.Count() == 3);
    assert(report.HasBlockingDiagnostic());
    assert(!TLogApiDiagnosticGate::AllowsProgress(report));

    auto summary = TLogApiDiagnosticSummary::From(report);
    assert(summary.error_count == 2);
    assert(summary.warning_count == 1);
    assert(summary.blocking_count == 2);

    auto view = TLogApiDiagnosticReportView::From(report);
    assert(view.count == 3);
    assert(view.has_blocking);
    assert(view.records.size() == 3);
    assert(view.records[0].code == "LOGAPI_CFG_NOT_READY");

    std::cout << "LOGAPI-W28 smoke test passed\\n";
    return 0;
}

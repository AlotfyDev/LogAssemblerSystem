#include "assembler/communication_context/diagnostics/TDiagnostics.hpp"

#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/registries/optional_registries/snapshots/TRegistrySnapshot.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W12_DIAGNOSTICS_AVAILABLE,
        "W12 diagnostics aggregate marker must be available");

    static_assert(
        ASCC_W11_OPTIONAL_REGISTRIES_AVAILABLE,
        "W11 optional registry aggregate should be visible through diagnostics dependencies");

    constexpr auto token = TCorrelationToken::from_parts(12u, 1u);

    auto completed_bridge = TBridgeCoreResult::completed(
        TBridgeId::from_value(1201u),
        8u,
        token,
        "bridge completed for diagnostics smoke test");

    auto bridge_record = TBridgeDiagnosticBuilder::from_result(
        TDiagnosticId::from_value(1u),
        completed_bridge);

    if (!bridge_record.is_valid())
    {
        return 1;
    }

    if (bridge_record.failed())
    {
        return 2;
    }

    if (bridge_record.severity != TDiagnosticSeverity::info)
    {
        return 3;
    }

    auto exhausted_bridge = TBridgeCoreResult::exhausted_budget(
        TBridgeId::from_value(1202u),
        2u,
        token);

    auto exhausted_record = TBridgeDiagnosticBuilder::from_result(
        TDiagnosticId::from_value(2u),
        exhausted_bridge);

    if (!exhausted_record.is_valid() || exhausted_record.severity != TDiagnosticSeverity::warning)
    {
        return 4;
    }

    auto registry_snapshot = TRegistrySnapshot::make(
        "w12_registry_snapshot",
        1u,
        4u,
        0u,
        token);

    auto registry_record = TRegistryDiagnosticBuilder::from_snapshot(
        TDiagnosticId::from_value(3u),
        registry_snapshot);

    if (!registry_record.is_valid())
    {
        return 5;
    }

    TDiagnosticCollector<8> collector =
        TDiagnosticCollector<8>::make("w12_smoke_collector", token);

    if (!collector.is_valid())
    {
        return 6;
    }

    if (!collector.add(bridge_record))
    {
        return 7;
    }

    if (!collector.add(exhausted_record))
    {
        return 8;
    }

    if (!collector.add(registry_record))
    {
        return 9;
    }

    auto snapshot = collector.snapshot();

    if (!snapshot.is_valid())
    {
        return 10;
    }

    if (snapshot.count != 3u)
    {
        return 11;
    }

    if (snapshot.failure_count != 0u)
    {
        return 12;
    }

    if (snapshot.highest_severity != TDiagnosticSeverity::warning)
    {
        return 13;
    }

    auto explicit_error = TDiagnosticRecord::error(
        TDiagnosticId::from_value(4u),
        TDiagnosticCategory::protocol,
        "protocol.synthetic_error",
        "synthetic_protocol",
        "synthetic error for diagnostics smoke",
        token);

    if (!collector.add_if_included(
            explicit_error,
            TDiagnosticPolicy::warnings_and_above()))
    {
        return 14;
    }

    auto snapshot2 = collector.snapshot();

    if (!snapshot2.has_failures())
    {
        return 15;
    }

    if (snapshot2.failure_count != 1u)
    {
        return 16;
    }

    if (snapshot2.highest_severity != TDiagnosticSeverity::error)
    {
        return 17;
    }

    auto view = TDiagnosticView::from_record(explicit_error);

    if (!view.is_valid() || !view.failed())
    {
        return 18;
    }

    return 0;
}

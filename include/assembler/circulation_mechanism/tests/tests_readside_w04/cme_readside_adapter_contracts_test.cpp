#include "assembler/circulation_mechanism/circulation_mechanism_read_side_adapter_contracts.hpp"

using namespace assembler::circulation_mechanism::read_side;

int main()
{
    constexpr TReadSidePayloadRef payload{TReadSidePayloadRef::from_raw(100)};

    constexpr auto in_process = TInProcessReceiverAdapterContract::make(
        TReadSideAdapterContractId::from_raw(1),
        TReadSideAdapterStatus::ready,
        false
    );
    static_assert(in_process.is_valid(), "in-process contract valid");
    static_assert(in_process.ready(), "in-process ready");
    static_assert(in_process.evaluate(payload, TReadSideAdapterCapabilityKind::accept_payload, false)
        == TReadSideAdapterInvocationStatus::accepted, "in-process accepts payload without external runtime");

    constexpr auto database = TDatabaseAdapterContract::make(
        TReadSideAdapterContractId::from_raw(2),
        TReadSideAdapterStatus::ready,
        true
    );
    static_assert(database.evaluate(payload, TReadSideAdapterCapabilityKind::persist_snapshot, true)
        == TReadSideAdapterInvocationStatus::accepted, "database persists when runtime available");

    constexpr auto file_sink = TFileSinkAdapterContract::make(
        TReadSideAdapterContractId::from_raw(3),
        TReadSideAdapterStatus::ready,
        true
    );
    static_assert(file_sink.evaluate(payload, TReadSideAdapterCapabilityKind::write_file, true)
        == TReadSideAdapterInvocationStatus::accepted, "file sink writes when runtime available");

    constexpr auto telemetry = TOpenTelemetryAdapterContract::make(
        TReadSideAdapterContractId::from_raw(4),
        TReadSideAdapterStatus::ready,
        true
    );
    static_assert(telemetry.evaluate(payload, TReadSideAdapterCapabilityKind::export_telemetry, true)
        == TReadSideAdapterInvocationStatus::accepted, "telemetry exports when runtime available");

    constexpr auto diag = TDiagnosticSinkAdapterContract::make(
        TReadSideAdapterContractId::from_raw(5),
        TReadSideAdapterStatus::ready,
        false
    );
    static_assert(diag.evaluate(payload, TReadSideAdapterCapabilityKind::emit_diagnostic, false)
        == TReadSideAdapterInvocationStatus::accepted, "diagnostic sink emits diagnostic");

    constexpr auto abi = TThinCAbiAdapterContract::make(
        TReadSideAdapterContractId::from_raw(6),
        TReadSideAdapterStatus::ready,
        true
    );
    static_assert(abi.evaluate(payload, TReadSideAdapterCapabilityKind::foreign_abi_call, true)
        == TReadSideAdapterInvocationStatus::accepted, "thin C ABI accepted when runtime available");

    constexpr TReadSideAdapterReport report{
        TReadSideAdapterContractId::from_raw(1),
        TReadSideAdapterKind::in_process_receiver,
        TReadSideAdapterInvocationStatus::accepted,
        TReadSideAdapterIssueKind::none
    };
    static_assert(report.accepted(), "adapter report accepted");

    return 0;
}

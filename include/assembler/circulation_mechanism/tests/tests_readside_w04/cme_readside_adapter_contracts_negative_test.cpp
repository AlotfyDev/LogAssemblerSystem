#include "assembler/circulation_mechanism/circulation_mechanism_read_side_adapter_contracts.hpp"

using namespace assembler::circulation_mechanism::read_side;

int main()
{
    constexpr TReadSidePayloadRef invalid_payload{TReadSidePayloadRef::invalid()};

    constexpr auto database = TDatabaseAdapterContract::make(
        TReadSideAdapterContractId::from_raw(2),
        TReadSideAdapterStatus::ready,
        true
    );

    static_assert(database.evaluate(invalid_payload, TReadSideAdapterCapabilityKind::persist_snapshot, true)
        == TReadSideAdapterInvocationStatus::rejected_payload_invalid, "invalid payload rejected");

    static_assert(database.evaluate(TReadSidePayloadRef::from_raw(10), TReadSideAdapterCapabilityKind::export_telemetry, true)
        == TReadSideAdapterInvocationStatus::rejected_capability_missing, "wrong capability rejected");

    static_assert(database.evaluate(TReadSidePayloadRef::from_raw(10), TReadSideAdapterCapabilityKind::persist_snapshot, false)
        == TReadSideAdapterInvocationStatus::rejected_external_runtime_required, "missing external runtime rejected");

    constexpr auto blocked = TFileSinkAdapterContract::make(
        TReadSideAdapterContractId::from_raw(3),
        TReadSideAdapterStatus::blocked,
        true
    );

    static_assert(blocked.evaluate(TReadSidePayloadRef::from_raw(10), TReadSideAdapterCapabilityKind::write_file, true)
        == TReadSideAdapterInvocationStatus::rejected_not_ready, "blocked adapter rejected");

    return 0;
}

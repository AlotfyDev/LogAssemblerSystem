#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapterBinding.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationTraits.hpp"
#include "assembler/communication_context/bridge_core/TBridgeCore.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W14A_LOG_LEVEL_API_ENVELOPE_PLUGIN_ADAPTER_AVAILABLE,
        "W14A aggregate marker must be available");

    static_assert(
        ASCC_W10_BRIDGE_CORE_AVAILABLE,
        "W10 aggregate marker must remain visible");

    static_assert(
        is_plugin_adapter_obligation_surface<TLogLevelAPIEnvelopePluginAdapter>::value,
        "TLogLevelAPIEnvelopePluginAdapter must satisfy W05 PluginAdapter obligation surface");

    constexpr auto token = TCorrelationToken::from_parts(14u, 1u);

    auto adapter = TLogLevelAPIEnvelopePluginAdapterFactory::from_fields(
        token,
        "env-0001",
        128u);

    auto adapter_view = adapter.view();

    if (!adapter_view.is_valid())
    {
        return 1;
    }

    if (!adapter_view.supports_primary_placement_flow())
    {
        return 2;
    }

    auto readiness = adapter.readiness();

    if (!readiness.is_ready())
    {
        return 3;
    }

    auto placement_request = adapter.prepare_placement_request();

    if (!placement_request.is_valid())
    {
        return 4;
    }

    if (placement_request.payload_kind != std::string_view{"log_level_envelope"})
    {
        return 5;
    }

    if (placement_request.requested_destination_family != std::string_view{"write_side"})
    {
        return 6;
    }

    auto bad_signal = adapter.emit_load_signal();

    if (!bad_signal.failed())
    {
        return 7;
    }

    auto handle = TPlacementHandle::make(
        42u,
        token,
        "write_side_envelope_slot");

    auto accept_result = adapter.accept_placement_handle(handle);

    if (!accept_result.succeeded())
    {
        return 8;
    }

    auto signal = adapter.emit_load_signal();

    if (!signal.completed())
    {
        return 9;
    }

    if (signal.bytes_loaded != 128u)
    {
        return 10;
    }

    auto next = adapter.next_destination_request();

    if (!next.is_valid())
    {
        return 11;
    }

    if (next.reason != TNextDestinationReason::continuous_flow_requested)
    {
        return 12;
    }

    auto wrong_handle_result = adapter.accept_placement_handle(
        TPlacementHandle::make(
            99u,
            TCorrelationToken::from_parts(14u, 2u),
            "wrong"));

    if (!wrong_handle_result.rejected())
    {
        return 13;
    }

    return 0;
}

#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPortBinding.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapterBinding.hpp"
#include "assembler/communication_context/obligations/ports/obligations/TPortObligationTraits.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationTraits.hpp"
#include "assembler/communication_context/bridge_core/TBridgeCore.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W14B_WRITE_SIDE_ENVELOPE_PLACEMENT_PORT_AVAILABLE,
        "W14B aggregate marker must be available");

    static_assert(
        ASCC_W14A_LOG_LEVEL_API_ENVELOPE_PLUGIN_ADAPTER_AVAILABLE,
        "W14A aggregate marker must remain visible");

    static_assert(
        ASCC_W10_BRIDGE_CORE_AVAILABLE,
        "W10 aggregate marker must remain visible");

    static_assert(
        is_port_obligation_surface<TWriteSideEnvelopePlacementPort>::value,
        "TWriteSideEnvelopePlacementPort must satisfy W05 Port obligation surface");

    static_assert(
        is_plugin_adapter_obligation_surface<TLogLevelAPIEnvelopePluginAdapter>::value,
        "TLogLevelAPIEnvelopePluginAdapter must satisfy W05 PluginAdapter obligation surface");

    constexpr auto token = TCorrelationToken::from_parts(14u, 2u);

    auto adapter = TLogLevelAPIEnvelopePluginAdapterFactory::from_fields(
        token,
        "env-0002",
        256u);

    auto port = TWriteSideEnvelopePlacementPortFactory::make_default();

    auto adapter_view = adapter.view();
    auto port_view = port.view();

    if (!adapter_view.is_valid() || !port_view.is_valid())
    {
        return 1;
    }

    if (!adapter_view.supports_primary_placement_flow() || !port_view.supports_primary_placement_flow())
    {
        return 2;
    }

    auto request = adapter.prepare_placement_request();

    if (!request.is_valid())
    {
        return 3;
    }

    auto readiness = port.readiness(request);

    if (!readiness.is_ready())
    {
        return 4;
    }

    auto admission = port.admit(request);

    if (!admission.accepted())
    {
        return 5;
    }

    auto handle = port.placement_handle(request);

    if (!handle.is_valid())
    {
        return 6;
    }

    auto adapter_accept = adapter.accept_placement_handle(handle);

    if (!adapter_accept.succeeded())
    {
        return 7;
    }

    auto signal = adapter.emit_load_signal();

    if (!signal.completed())
    {
        return 8;
    }

    auto port_receive = port.receive_load_signal(signal);

    if (!port_receive.succeeded())
    {
        return 9;
    }

    if (!port.state().has_completed_load())
    {
        return 10;
    }

    auto next_request = adapter.next_destination_request();
    auto next_result = port.next_destination(next_request);

    if (!next_result.succeeded())
    {
        return 11;
    }

    auto wrong_request = TPlacementRequest::make(
        token,
        "unsupported_payload",
        12u,
        true,
        "write_side");

    auto wrong_readiness = port.readiness(wrong_request);

    if (wrong_readiness.is_ready())
    {
        return 12;
    }

    auto wrong_admission = port.admit(wrong_request);

    if (!wrong_admission.rejected())
    {
        return 13;
    }

    auto invalid_handle = port.placement_handle(wrong_request);

    if (invalid_handle.is_valid())
    {
        return 14;
    }

    auto mismatched_signal = TLoadSignal::completed(
        token,
        TPlacementHandle::make(
            9999u,
            token,
            "write_side_envelope_slot"),
        8u);

    auto mismatch_result = port.receive_load_signal(mismatched_signal);

    if (!mismatch_result.rejected())
    {
        return 15;
    }

    return 0;
}

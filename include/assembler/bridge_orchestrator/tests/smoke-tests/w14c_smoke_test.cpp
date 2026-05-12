#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/TWriteSideRegistryDeliveryPluginAdapterBinding.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W14C_WRITE_SIDE_REGISTRY_DELIVERY_PLUGIN_ADAPTER_AVAILABLE,
        "W14C aggregate marker must be available");

    static_assert(
        ASCC_W13_INTEGRATION_BOUNDARY_ABSTRACT_PORTS_AVAILABLE,
        "W13 aggregate marker must be visible through W14C dependencies");

    auto token = TCorrelationToken::from_parts(14u, 3u);

    auto adapter = TWriteSideRegistryDeliveryPluginAdapterFactory::from_fields(
        token,
        "w14c-write-side-material",
        512u,
        true);

    if (!adapter.descriptor().is_valid())
    {
        return 1;
    }

    if (!adapter.config().is_valid())
    {
        return 2;
    }

    auto view = adapter.view();

    if (!view.is_valid())
    {
        return 3;
    }

    if (view.obligation_profile.family != TPluginAdapterObligationFamily::delivery_content_provider)
    {
        return 4;
    }

    auto readiness = adapter.readiness();

    if (!readiness.is_ready())
    {
        return 5;
    }

    auto placement_request = adapter.prepare_placement_request();

    if (!placement_request.is_valid())
    {
        return 6;
    }

    if (placement_request.requested_destination_family != "registry_delivery")
    {
        return 7;
    }

    auto boundary_request = adapter.prepare_boundary_handoff_request();

    if (!boundary_request.is_valid())
    {
        return 8;
    }

    if (boundary_request.target.kind != TIntegrationBoundaryKind::registry_delivery)
    {
        return 9;
    }

    auto placement_handle = TPlacementHandle::make(
        1403001u,
        token,
        "registry_delivery");

    auto handle_result = adapter.accept_placement_handle(placement_handle);

    if (!handle_result.succeeded())
    {
        return 10;
    }

    auto load_signal = adapter.emit_load_signal();

    if (!load_signal.completed())
    {
        return 11;
    }

    auto next_destination = adapter.next_destination_request();

    if (!next_destination.is_valid()
        || next_destination.reason != TNextDestinationReason::current_destination_completed)
    {
        return 12;
    }

    auto boundary_handle = TBoundaryHandoffHandle::make(
        1403002u,
        TIntegrationBoundaryKind::registry_delivery,
        token,
        "registry_delivery_handoff");

    auto boundary_result = TBoundaryHandoffResult::accepted(boundary_handle);

    auto accepted_boundary_bridge_result =
        adapter.accept_boundary_handoff_result(boundary_result);

    if (!accepted_boundary_bridge_result.succeeded())
    {
        return 13;
    }

    if (!adapter.state().has_accepted_boundary_handle())
    {
        return 14;
    }

    auto completed_boundary_bridge_result =
        adapter.accept_boundary_handoff_result(
            TBoundaryHandoffResult::completed(boundary_handle));

    if (!completed_boundary_bridge_result.succeeded())
    {
        return 15;
    }

    if (!adapter.state().boundary_handoff_completed)
    {
        return 16;
    }

    adapter.reset_state();

    if (adapter.state().has_accepted_placement_handle()
        || adapter.state().has_accepted_boundary_handle())
    {
        return 17;
    }

    return 0;
}

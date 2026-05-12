#include "assembler/communication_context/registries/TOptionalRegistries.hpp"

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bindings/profiles/TBindingProfile.hpp"
#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/obligations/ports/obligations/TPortObligationProfile.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationProfile.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"
#include "assembler/communication_context/protocols/plans/TBridgeProtocolPlan.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W11_OPTIONAL_REGISTRIES_AVAILABLE,
        "W11 optional registry aggregate must be available");

    auto token = TCorrelationToken::from_parts(11u, 1u);

    auto source = TParticipant::make(
        101u,
        TParticipantRole::content_provider,
        "log_level_api",
        "envelope_plugin_adapter",
        "test_content_provider",
        token);

    auto target = TParticipant::make(
        202u,
        TParticipantRole::host_provider,
        "write_side",
        "envelope_placement_port",
        "test_host_provider",
        token);

    auto channel = TChannel::declare(
        301u,
        source,
        target,
        TSingleAdapterSinglePortProfile::make(),
        TChannelBindingPolicy::strict_static_one_to_one(),
        "test_channel",
        token);

    auto adapter_view = TPluginAdapterView::make(
        401u,
        TParticipantView::from_participant(source),
        TPluginAdapterObligationProfile::placement_content_provider(),
        "test_adapter",
        token);

    auto port_view = TPortView::make(
        501u,
        TParticipantView::from_participant(target),
        TPortObligationProfile::placement_host("test_port_obligation"),
        "test_port",
        token);

    auto surface_pair = TObligationSurfacePair::make(adapter_view, port_view);

    auto binding = TBinding::propose(
        TBindingId::from_value(601u),
        channel,
        surface_pair,
        TBindingProfile::strict_static_one_to_one(),
        "test_binding",
        token);

    auto session = TSession::open(
        TSessionOpenRequest::make(
            TSessionId::from_value(701u),
            binding,
            TSessionPolicy::strict_declaration_session(),
            "test_session",
            token));

    auto protocol = TBridgeProtocol<12>::declare(
        TBridgeProtocolId::from_value(801u),
        session,
        TBridgeProtocolPlan<12>::envelope_placement_plan(),
        "test_protocol",
        token);

    auto bridge = TBridge<12>::declare(
        TBridgeId::from_value(901u),
        protocol,
        TBridgeConfig::bounded_model_run(16u),
        "test_bridge",
        token);

    if (!channel.is_valid())
    {
        return 1;
    }

    if (!binding.is_compatible())
    {
        return 2;
    }

    if (!session.is_open())
    {
        return 3;
    }

    if (!protocol.is_ready())
    {
        return 4;
    }

    if (!bridge.is_ready())
    {
        return 5;
    }

    auto registry_set =
        TCommunicationContextRegistrySet<4, 4, 4, 4, 4, 12>::make(token);

    if (!registry_set.is_valid())
    {
        return 6;
    }

    if (!registry_set.channels.register_channel(channel))
    {
        return 7;
    }

    if (!registry_set.bindings.register_binding(binding))
    {
        return 8;
    }

    if (!registry_set.sessions.register_session(session))
    {
        return 9;
    }

    if (!registry_set.protocols.register_protocol(protocol))
    {
        return 10;
    }

    if (!registry_set.bridges.register_bridge(bridge))
    {
        return 11;
    }

    if (registry_set.total_count() != 5u)
    {
        return 12;
    }

    if (!registry_set.channels.contains(301u))
    {
        return 13;
    }

    if (!registry_set.bindings.contains(TBindingId::from_value(601u)))
    {
        return 14;
    }

    if (!registry_set.sessions.contains(TSessionId::from_value(701u)))
    {
        return 15;
    }

    if (!registry_set.protocols.contains(TBridgeProtocolId::from_value(801u)))
    {
        return 16;
    }

    if (!registry_set.bridges.contains(TBridgeId::from_value(901u)))
    {
        return 17;
    }

    if (registry_set.bindings.register_binding(binding))
    {
        return 18;
    }

    auto snapshot = registry_set.bindings.snapshot();

    if (!snapshot.is_valid() || snapshot.count != 1u || snapshot.rejected_insertions != 1u)
    {
        return 19;
    }

    return 0;
}

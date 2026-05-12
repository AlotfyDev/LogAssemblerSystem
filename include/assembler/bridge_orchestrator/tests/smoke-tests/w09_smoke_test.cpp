#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/plans/TBridgeProtocolPlan.hpp"
#include "assembler/communication_context/protocols/status/TBridgeProtocolStatus.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"
#include "assembler/communication_context/sessions/status/TSessionStatus.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationProfile.hpp"
#include "assembler/communication_context/obligations/ports/obligations/TPortObligationProfile.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"
#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/bindings/profiles/TBindingProfile.hpp"

using namespace assembler::communication_context;

int main()
{
    constexpr auto token = TCorrelationToken::from_parts(9u, 1u);

    constexpr auto source = TParticipant::make(
        100u,
        TParticipantRole::content_provider,
        "log_level_api",
        "envelope_adapter",
        "Log Level API Adapter",
        token);

    constexpr auto target = TParticipant::make(
        200u,
        TParticipantRole::host_provider,
        "write_side",
        "placement_port",
        "Write Side Placement Port",
        token);

    constexpr auto channel = TChannel::declare(
        300u,
        source,
        target,
        TSingleAdapterSinglePortProfile::make(),
        TChannelBindingPolicy::strict_static_one_to_one(),
        "log_level_api_to_write_side",
        token);

    constexpr auto adapter_view = TPluginAdapterView::make(
        400u,
        TParticipantView::from_participant(source),
        TPluginAdapterObligationProfile::placement_content_provider(),
        "adapter_view",
        token);

    constexpr auto port_view = TPortView::make(
        500u,
        TParticipantView::from_participant(target),
        TPortObligationProfile::placement_host(),
        "port_view",
        token);

    constexpr auto pair = TObligationSurfacePair::make(adapter_view, port_view);

    constexpr auto binding = TBinding::propose(
        TBindingId::from_value(700u),
        channel,
        pair,
        TBindingProfile::strict_static_one_to_one(),
        "bridge_protocol_binding",
        token);

    constexpr auto request = TSessionOpenRequest::make(
        TSessionId::from_value(800u),
        binding,
        TSessionPolicy::strict_declaration_session(),
        "bridge_protocol_session",
        token);

    constexpr auto session = TSession::open(request);

    static_assert(session.is_open(), "session must be open before protocol declaration");

    constexpr auto plan = TBridgeProtocolPlan<12>::envelope_placement_plan();

    static_assert(plan.is_valid(), "plan must be valid");
    static_assert(plan.kind == TBridgeProtocolKind::envelope_placement, "plan must be envelope placement");
    static_assert(plan.step_count == 12u, "envelope placement plan must contain twelve steps");

    constexpr auto declared = TBridgeProtocol<12>::declare(
        TBridgeProtocolId::from_value(900u),
        session,
        plan,
        "bridge_protocol_model_test",
        token);

    static_assert(declared.is_valid(), "declared protocol must be valid");
    static_assert(declared.is_ready(), "declared protocol must be ready");
    static_assert(declared.view().is_valid(), "protocol view must be valid");
    static_assert(declared.frame().is_valid(), "protocol frame must be valid");
    static_assert(declared.trace_current_step("initial").is_valid(), "initial trace must be valid");

    auto protocol = declared;

    for (std::size_t index = 0u; index < plan.step_count; ++index)
    {
        const auto result = protocol.advance_model_step();

        if (index + 1u < plan.step_count)
        {
            if (!result.succeeded() || !protocol.is_active())
            {
                return 1;
            }
        }
        else
        {
            if (!result.succeeded() || protocol.status != TBridgeProtocolStatus::completed)
            {
                return 2;
            }
        }
    }

    if (!protocol.is_terminal())
    {
        return 3;
    }

    if (protocol.session.status != TSessionStatus::completed)
    {
        return 4;
    }

    if (!protocol.last_result.succeeded())
    {
        return 5;
    }

    auto invalid_protocol = TBridgeProtocol<12>::declare(
        TBridgeProtocolId::from_value(901u),
        TSession{},
        plan,
        "invalid_bridge_protocol_model_test",
        token);

    if (invalid_protocol.status != TBridgeProtocolStatus::rejected)
    {
        return 6;
    }

    return 0;
}

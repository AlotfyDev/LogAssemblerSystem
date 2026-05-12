#include "assembler/communication_context/bridge_core/TBridgeCore.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"

using namespace assembler::communication_context;

int main()
{
    constexpr auto token = TCorrelationToken::from_parts(10u, 1u);

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
        "bridge_core_binding",
        token);

    constexpr auto request = TSessionOpenRequest::make(
        TSessionId::from_value(800u),
        binding,
        TSessionPolicy::strict_declaration_session(),
        "bridge_core_session",
        token);

    constexpr auto session = TSession::open(request);

    static_assert(session.is_open(), "session must be open before protocol declaration");

    constexpr auto plan = TBridgeProtocolPlan<12>::envelope_placement_plan();

    constexpr auto protocol = TBridgeProtocol<12>::declare(
        TBridgeProtocolId::from_value(900u),
        session,
        plan,
        "bridge_core_protocol",
        token);

    static_assert(protocol.is_ready(), "protocol must be ready before bridge declaration");

    constexpr auto bridge = TBridge<12>::declare(
        TBridgeId::from_value(1000u),
        protocol,
        TBridgeConfig::bounded_model_run(12u),
        "bridge_core_test",
        token);

    static_assert(bridge.is_valid(), "bridge must be valid");
    static_assert(bridge.is_ready(), "bridge must be ready");
    static_assert(bridge.view().is_valid(), "bridge view must be valid");
    static_assert(bridge.snapshot().is_valid(), "bridge snapshot must be valid");
    static_assert(ASCC_W10_BRIDGE_CORE_AVAILABLE, "aggregate include marker must exist");

    auto running_bridge = bridge;

    auto first_report = running_bridge.step_model_report();

    if (!first_report.is_valid())
    {
        return 1;
    }

    if (!first_report.succeeded())
    {
        return 2;
    }

    if (running_bridge.status != TBridgeStatus::running)
    {
        return 3;
    }

    auto final_result = running_bridge.run_model_to_terminal();

    if (!final_result.completed())
    {
        return 4;
    }

    if (running_bridge.status != TBridgeStatus::completed)
    {
        return 5;
    }

    if (!running_bridge.is_terminal())
    {
        return 6;
    }

    if (running_bridge.config.budget.consumed_steps != 12u)
    {
        return 7;
    }

    if (running_bridge.protocol.status != TBridgeProtocolStatus::completed)
    {
        return 8;
    }

    auto exhausted_bridge = TBridge<12>::declare(
        TBridgeId::from_value(1001u),
        protocol,
        TBridgeConfig::bounded_model_run(2u),
        "bridge_core_exhaustion_test",
        token);

    auto exhausted_result = exhausted_bridge.run_model_to_terminal();

    if (!exhausted_result.exhausted())
    {
        return 9;
    }

    if (exhausted_bridge.status != TBridgeStatus::exhausted)
    {
        return 10;
    }

    auto invalid_bridge = TBridge<12>::declare(
        TBridgeId::invalid(),
        protocol,
        TBridgeConfig::bounded_model_run(12u),
        "bridge_core_invalid_test",
        token);

    if (invalid_bridge.status != TBridgeStatus::rejected)
    {
        return 11;
    }

    return 0;
}

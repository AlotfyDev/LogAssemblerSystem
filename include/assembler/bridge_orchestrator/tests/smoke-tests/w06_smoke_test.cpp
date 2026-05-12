#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"

using namespace assembler::communication_context;

int main()
{
    constexpr auto token = TCorrelationToken::from_parts(6u, 1u);

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

    static_assert(channel.is_valid(), "channel must be valid");

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

    static_assert(pair.supports_primary_placement_flow(), "surface pair must support placement flow");

    constexpr auto report = TBindingCompatibilityReport::evaluate(channel, pair, token);

    static_assert(report.is_compatible(), "binding compatibility report must be compatible");

    constexpr auto binding = TBinding::propose(
        TBindingId::from_value(600u),
        channel,
        pair,
        TBindingProfile::strict_static_one_to_one(),
        "binding_model_test",
        token);

    static_assert(binding.is_valid(), "binding must be valid");
    static_assert(binding.is_compatible(), "binding must be compatible");
    static_assert(binding.view().is_usable(), "binding view must be usable");
    static_assert(binding.result().accepted(), "binding result must be accepted");

    constexpr auto materialized = TBinding::materialize_declaration_only(binding);

    static_assert(materialized.is_materialized(), "materialized binding must be marked materialized");

    return materialized.result().accepted() ? 0 : 1;
}

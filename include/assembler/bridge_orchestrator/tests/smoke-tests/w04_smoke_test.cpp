#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/channels/profiles/TChannelProfile.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"

int main()
{
    using namespace assembler::communication_context;

    constexpr auto token = TCorrelationToken::from_parts(300u, 400u);
    static_assert(token.is_valid(), "token should be valid");

    constexpr auto profile = TSingleAdapterSinglePortProfile::make();
    static_assert(profile.is_valid(), "profile should be valid");
    static_assert(profile.is_one_to_one(), "profile should be one-to-one");
    static_assert(TSingleAdapterSinglePortProfile::matches(profile), "profile should match preset");

    constexpr auto policy = TChannelBindingPolicy::strict_static_one_to_one();
    static_assert(policy.is_valid(), "policy should be valid");
    static_assert(policy.is_static(), "policy should be static");
    static_assert(policy.is_strict_one_to_one(), "policy should be strict one-to-one");
    static_assert(policy.is_compatible_with(profile), "policy should be compatible with profile");

    constexpr auto source = TParticipant::make(
        1u,
        TParticipantRole::content_provider,
        "log_level_api",
        "envelope_plugin_adapter",
        "Log Level API Envelope Plugin Adapter",
        token);

    constexpr auto target = TParticipant::make(
        2u,
        TParticipantRole::host_provider,
        "write_side",
        "envelope_placement_port",
        "Write Side Envelope Placement Port",
        token);

    constexpr auto channel = TChannel::declare(
        10u,
        source,
        target,
        profile,
        policy,
        "log_level_api_to_write_side_envelope_placement",
        token);

    static_assert(channel.has_valid_identity(), "channel identity should be valid");
    static_assert(channel.has_valid_participants(), "channel participants should be valid");
    static_assert(channel.has_compatible_roles(), "channel roles should be compatible");
    static_assert(channel.is_valid(), "channel should be valid");

    static_assert(!is_terminal_bridge_stage(TBridgeStage::idle), "W02 include path should work");

    return 0;
}

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"

int main()
{
    using namespace assembler::communication_context;

    constexpr auto token = TCorrelationToken::from_parts(100u, 200u);
    static_assert(token.is_valid(), "token should be valid");

    static_assert(is_provider_role(TParticipantRole::content_provider), "content provider is provider");
    static_assert(is_provider_role(TParticipantRole::host_provider), "host provider is provider");
    static_assert(is_boundary_role(TParticipantRole::persistence_provider), "persistence provider is boundary");
    static_assert(!is_boundary_role(TParticipantRole::content_provider), "content provider is not boundary by default");
    static_assert(participates_in_primary_exchange(TParticipantRole::host_provider), "host provider participates in primary exchange");

    constexpr auto participant = TParticipant::make(
        1u,
        TParticipantRole::content_provider,
        "log_level_api",
        "envelope_plugin_adapter",
        "Log Level API Envelope Plugin Adapter",
        token);

    static_assert(participant.is_valid(), "participant should be valid");
    static_assert(participant.is_provider(), "participant should be provider");
    static_assert(participant.participates_in_exchange(), "participant should participate in primary exchange");

    constexpr auto view = TParticipantView::from_participant(participant);
    static_assert(view.is_valid(), "participant view should be valid");
    static_assert(view.is_provider(), "participant view should be provider");

    static_assert(!is_terminal_bridge_stage(TBridgeStage::idle), "W02 include path should work");

    return 0;
}

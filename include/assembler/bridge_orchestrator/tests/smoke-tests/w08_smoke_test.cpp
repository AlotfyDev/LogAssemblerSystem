#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"

using namespace assembler::communication_context;

int main()
{
    constexpr auto token = TCorrelationToken::from_parts(8u, 1u);

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
        "session_model_binding",
        token);

    static_assert(binding.is_compatible(), "binding must be compatible before opening session");
    static_assert(TCompatibilityEvaluator::is_strictly_compatible(binding), "W07 compatibility must pass");

    constexpr auto request = TSessionOpenRequest::make(
        TSessionId::from_value(800u),
        binding,
        TSessionPolicy::strict_declaration_session(),
        "session_model_test",
        token);

    static_assert(request.is_valid(), "session open request must be valid");
    static_assert(request.is_openable(), "compatible binding must be openable under declaration policy");

    constexpr auto session = TSession::open(request);

    static_assert(session.is_valid(), "session must be valid");
    static_assert(session.is_open(), "session must open");
    static_assert(!session.is_terminal(), "newly opened session must not be terminal");
    static_assert(session.view().is_valid(), "session view must be valid");
    static_assert(session.snapshot().is_valid(), "session snapshot must be valid");
    static_assert(session.result().succeeded(), "open session result must succeed");

    constexpr auto invalid_request = TSessionOpenRequest::make(
        TSessionId::from_value(801u),
        TBinding{},
        TSessionPolicy::strict_declaration_session(),
        "invalid_session_model_test",
        token);

    static_assert(!invalid_request.is_openable(), "invalid binding must not be openable");

    constexpr auto rejected_session = TSession::open(invalid_request);

    static_assert(rejected_session.is_valid(), "rejected session still records request context");
    static_assert(rejected_session.status == TSessionStatus::rejected, "invalid request must produce rejected session");
    static_assert(rejected_session.is_terminal(), "rejected session must be terminal");
    static_assert(rejected_session.result().rejected(), "rejected session result must reject");

    auto mutable_session = TSession::open(request);
    const auto activated = mutable_session.activate();
    const auto completed = mutable_session.complete();

    return session.is_open()
        && activated
        && completed
        && mutable_session.status == TSessionStatus::completed
        && rejected_session.result().rejected()
        ? 0
        : 1;
}

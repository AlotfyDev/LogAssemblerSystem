#include "assembler/communication_context/compatibility/TCompatibilityEvaluator.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"

using namespace assembler::communication_context;

int main()
{
    constexpr auto token = TCorrelationToken::from_parts(7u, 1u);

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
        "compatibility_model_test",
        token);

    static_assert(binding.is_compatible(), "binding must be compatible before W07 evaluation");

    constexpr auto matrix = TCompatibilityEvaluator::evaluate_strict_binding(binding);

    static_assert(matrix.compatible(), "strict compatibility matrix must pass");
    static_assert(matrix.issue_count == 0u, "valid binding should produce no compatibility issues");
    static_assert(TCompatibilityEvaluator::is_strictly_compatible(binding), "binding must be strictly compatible");

    constexpr auto view = TCompatibilityEvaluator::view_strict_binding(binding);

    static_assert(view.passed(), "compatibility view must pass");
    static_assert(!view.needs_review(), "clean compatibility should not need review");

    constexpr auto invalid_binding = TBinding{};

    constexpr auto invalid_matrix = TCompatibilityEvaluator::evaluate_strict_binding(invalid_binding);

    static_assert(!invalid_matrix.compatible(), "invalid binding must not pass compatibility");
    static_assert(invalid_matrix.blocking_count() > 0u, "invalid binding must produce blocking issues");

    return view.passed() && invalid_matrix.has_blocking_issues() ? 0 : 1;
}

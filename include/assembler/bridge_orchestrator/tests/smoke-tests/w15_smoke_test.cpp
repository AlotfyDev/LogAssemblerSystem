#include "assembler/communication_context/integration_boundaries/integration_skeleton/TFirstIntegrationSkeletonBinding.hpp"

using namespace assembler::communication_context;

int main()
{
    static_assert(
        ASCC_W15_FIRST_INTEGRATION_SKELETON_AVAILABLE,
        "W15 aggregate marker must be available");

    static_assert(
        ASCC_W14A_LOG_LEVEL_API_ENVELOPE_PLUGIN_ADAPTER_AVAILABLE,
        "W14A aggregate marker must be visible through W15 includes");

    static_assert(
        ASCC_W14B_WRITE_SIDE_ENVELOPE_PLACEMENT_PORT_AVAILABLE,
        "W14B aggregate marker must be visible through W15 includes");

    static_assert(
        ASCC_W10_BRIDGE_CORE_AVAILABLE,
        "W10 aggregate marker must remain visible");

    constexpr auto config = TFirstIntegrationSkeletonConfig::defaults();
    static_assert(config.is_valid(), "W15 default config must be valid");

    auto skeleton = TFirstIntegrationSkeletonFactory::make_default();
    auto report = skeleton.run();

    if (!report.succeeded())
    {
        return 1;
    }

    if (!report.model_succeeded())
    {
        return 2;
    }

    if (!report.flow_succeeded())
    {
        return 3;
    }

    if (!report.bridge_model_completed)
    {
        return 4;
    }

    if (!report.placement_handle_valid)
    {
        return 5;
    }

    if (!report.next_destination_acknowledged)
    {
        return 6;
    }

    auto explicit_skeleton = TFirstIntegrationSkeletonFactory::from_config_and_token(
        config,
        TCorrelationToken::from_parts(15u, 99u));

    auto explicit_report = explicit_skeleton.run();

    if (!explicit_report.succeeded())
    {
        return 7;
    }

    return 0;
}

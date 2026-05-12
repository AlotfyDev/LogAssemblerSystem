#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/obligations/ports/TPort.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/contracts/TPluginAdapter.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"

using namespace assembler::communication_context;

struct DummyPort final : TPort<DummyPort>
{
    TCorrelationToken token{TCorrelationToken::from_parts(1u, 2u)};

    [[nodiscard]] constexpr TPortView view() const noexcept
    {
        const auto participant = TParticipant::make(
            10u,
            TParticipantRole::host_provider,
            "write_side",
            "placement_host",
            "Dummy Host Port",
            token);

        return TPortView::make(
            100u,
            TParticipantView::from_participant(participant),
            TPortObligationProfile::placement_host(),
            "dummy_port",
            token);
    }

    [[nodiscard]] constexpr TReadinessView readiness(const TPlacementRequest&) noexcept
    {
        return TReadinessView::ready(token, 1u);
    }

    [[nodiscard]] constexpr TAdmissionResult admit(const TPlacementRequest&) noexcept
    {
        return TAdmissionResult::accept(token);
    }

    [[nodiscard]] constexpr TPlacementHandle placement_handle(const TPlacementRequest&) noexcept
    {
        return TPlacementHandle::make(77u, token, "dummy_handle");
    }

    [[nodiscard]] constexpr TBridgeResult receive_load_signal(const TLoadSignal&) noexcept
    {
        return TBridgeResult::success(token);
    }

    [[nodiscard]] constexpr TBridgeResult next_destination(const TNextDestinationRequest&) noexcept
    {
        return TBridgeResult::success(token);
    }
};

struct DummyPluginAdapter final : TPluginAdapter<DummyPluginAdapter>
{
    TCorrelationToken token{TCorrelationToken::from_parts(1u, 2u)};
    TPlacementHandle current_handle{TPlacementHandle::invalid()};

    [[nodiscard]] constexpr TPluginAdapterView view() const noexcept
    {
        const auto participant = TParticipant::make(
            20u,
            TParticipantRole::content_provider,
            "log_level_api",
            "placement_content_adapter",
            "Dummy Content Adapter",
            token);

        return TPluginAdapterView::make(
            200u,
            TParticipantView::from_participant(participant),
            TPluginAdapterObligationProfile::placement_content_provider(),
            "dummy_adapter",
            token);
    }

    [[nodiscard]] constexpr TReadinessView readiness() noexcept
    {
        return TReadinessView::ready(token, 1u);
    }

    [[nodiscard]] constexpr TPlacementRequest prepare_placement_request() noexcept
    {
        return TPlacementRequest::make(token, "log_level_envelope", 64u, true, "write_side");
    }

    [[nodiscard]] constexpr TBridgeResult accept_placement_handle(const TPlacementHandle& handle) noexcept
    {
        current_handle = handle;
        return handle.is_valid()
            ? TBridgeResult::success(token)
            : TBridgeResult::fail(TBridgeError::make(TBridgeErrorCode::handle_unavailable), token);
    }

    [[nodiscard]] constexpr TLoadSignal emit_load_signal() noexcept
    {
        return TLoadSignal::completed(token, current_handle, 64u);
    }

    [[nodiscard]] constexpr TNextDestinationRequest next_destination_request() noexcept
    {
        return TNextDestinationRequest::make(
            token,
            current_handle,
            TNextDestinationReason::continuous_flow_requested,
            "continue");
    }
};

int main()
{
    static_assert(is_port_obligation_surface<DummyPort>::value, "DummyPort must satisfy port obligation surface");
    static_assert(is_plugin_adapter_obligation_surface<DummyPluginAdapter>::value, "DummyPluginAdapter must satisfy plugin adapter surface");

    DummyPort port;
    DummyPluginAdapter adapter;

    auto adapter_readiness = adapter.readiness();
    if (!adapter_readiness.is_ready())
    {
        return 1;
    }

    auto request = adapter.prepare_placement_request();
    if (!request.is_valid())
    {
        return 2;
    }

    auto port_readiness = port.readiness(request);
    if (!port_readiness.is_ready())
    {
        return 3;
    }

    auto admission = port.admit(request);
    if (!admission.accepted())
    {
        return 4;
    }

    auto handle = port.placement_handle(request);
    if (!handle.is_valid())
    {
        return 5;
    }

    auto accept_handle_result = adapter.accept_placement_handle(handle);
    if (!accept_handle_result.succeeded())
    {
        return 6;
    }

    auto load_signal = adapter.emit_load_signal();
    if (!load_signal.completed())
    {
        return 7;
    }

    auto signal_result = port.receive_load_signal(load_signal);
    if (!signal_result.succeeded())
    {
        return 8;
    }

    auto next_request = adapter.next_destination_request();
    if (!next_request.is_valid())
    {
        return 9;
    }

    auto next_result = port.next_destination(next_request);
    if (!next_result.succeeded())
    {
        return 10;
    }

    auto pair = TObligationSurfacePair::make(adapter.view(), port.view());
    if (!pair.supports_primary_placement_flow())
    {
        return 11;
    }

    auto report = pair.report_primary_placement_support();
    if (!report.is_satisfied())
    {
        return 12;
    }

    return 0;
}

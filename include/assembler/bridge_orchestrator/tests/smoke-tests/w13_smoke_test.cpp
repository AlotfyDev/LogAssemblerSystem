#include "assembler/communication_context/integration_boundaries/TIntegrationBoundaryAbstractPorts.hpp"

using namespace assembler::communication_context;

class TMockPersistenceBoundaryPort final
    : public TIntegrationBoundaryPort<TMockPersistenceBoundaryPort>
{
public:
    constexpr TMockPersistenceBoundaryPort(
        TIntegrationBoundaryDescriptor descriptor,
        std::uint64_t first_handle = 1300u) noexcept
        : descriptor_(descriptor),
          next_handle_(first_handle)
    {
    }

    [[nodiscard]] constexpr TIntegrationBoundaryPortView boundary_view() const noexcept
    {
        return TIntegrationBoundaryPortView::make(
            descriptor_,
            "mock_persistence_boundary_port",
            "ready",
            descriptor_.correlation);
    }

    [[nodiscard]] constexpr TIntegrationBoundaryDescriptor boundary_descriptor() const noexcept
    {
        return descriptor_;
    }

    [[nodiscard]] constexpr TReadinessView boundary_readiness(
        const TBoundaryHandoffRequest& request) noexcept
    {
        return TIntegrationBoundaryPolicy::request_readiness(request);
    }

    [[nodiscard]] constexpr TBoundaryHandoffResult accept_boundary_handoff(
        const TBoundaryHandoffRequest& request) noexcept
    {
        auto readiness = boundary_readiness(request);

        if (!readiness.is_ready())
        {
            return TBoundaryHandoffResult::deferred(
                TBridgeError::make(TBridgeErrorCode::admission_deferred, readiness.reason),
                request.correlation);
        }

        auto handle = TBoundaryHandoffHandle::make(
            next_handle_++,
            request.target.kind,
            request.correlation,
            "mock_persistence_handoff");

        return TBoundaryHandoffResult::accepted(handle);
    }

    [[nodiscard]] constexpr TBoundaryHandoffResult complete_boundary_handoff(
        const TBoundaryHandoffHandle& handle) noexcept
    {
        if (!handle.is_valid())
        {
            return TBoundaryHandoffResult::failed(
                TBridgeError::make(TBridgeErrorCode::handle_unavailable, "boundary handle invalid"),
                handle.correlation);
        }

        return TBoundaryHandoffResult::completed(handle);
    }

    [[nodiscard]] constexpr TBoundaryHandoffResult reject_boundary_handoff(
        const TBoundaryHandoffRequest& request) noexcept
    {
        return TBoundaryHandoffResult::rejected(
            TBridgeError::make(TBridgeErrorCode::admission_rejected, "mock rejection"),
            request.correlation);
    }

private:
    TIntegrationBoundaryDescriptor descriptor_{};
    std::uint64_t next_handle_{0u};
};

static_assert(
    TIntegrationBoundaryPortTraits<TMockPersistenceBoundaryPort>::satisfies_required_surface,
    "Mock boundary port must satisfy W13 required surface");

int main()
{
    static_assert(
        ASCC_W13_INTEGRATION_BOUNDARY_ABSTRACT_PORTS_AVAILABLE,
        "W13 aggregate marker must be available");

    static_assert(
        ASCC_W12_DIAGNOSTICS_AVAILABLE,
        "W12 diagnostics aggregate marker must be visible through W13 aggregate");

    constexpr auto token = TCorrelationToken::from_parts(13u, 1u);

    auto descriptor = TIntegrationBoundaryDescriptor::persistence(token);

    if (!descriptor.is_valid())
    {
        return 1;
    }

    if (!descriptor.has(TIntegrationBoundaryCapability::accepts_handoff))
    {
        return 2;
    }

    if (!TIntegrationBoundaryPolicy::supports_outbound_handoff(descriptor))
    {
        return 3;
    }

    TMockPersistenceBoundaryPort port{descriptor};

    auto view = port.boundary_view();

    if (!view.is_valid())
    {
        return 4;
    }

    auto request = TBoundaryHandoffRequest::make(
        token,
        descriptor,
        "log_level_envelope",
        256u,
        false);

    if (!request.is_valid())
    {
        return 5;
    }

    auto readiness = port.boundary_readiness(request);

    if (!readiness.is_ready())
    {
        return 6;
    }

    auto accepted = port.accept_boundary_handoff(request);

    if (!accepted.accepted())
    {
        return 7;
    }

    if (!accepted.handle.is_valid())
    {
        return 8;
    }

    auto completed = port.complete_boundary_handoff(accepted.handle);

    if (!completed.completed())
    {
        return 9;
    }

    auto rejected = port.reject_boundary_handoff(request);

    if (!rejected.failed() || rejected.status != TBoundaryHandoffStatus::rejected)
    {
        return 10;
    }

    auto diagnostic = TDiagnosticRecord::info(
        TDiagnosticId::from_value(13u),
        TDiagnosticCategory::boundary,
        "boundary.abstract_port_smoke",
        "mock_persistence_boundary_port",
        "W13 smoke diagnostic",
        token);

    auto report = TIntegrationBoundaryReport::make(
        view,
        completed,
        diagnostic,
        "mock boundary report");

    if (!report.is_valid() || report.failed())
    {
        return 11;
    }

    auto ordered_descriptor = TIntegrationBoundaryDescriptor::read_side(token);
    auto ordered_request = TBoundaryHandoffRequest::make(
        token,
        ordered_descriptor,
        "log_level_envelope",
        128u,
        true);

    auto ordered_readiness =
        TIntegrationBoundaryPolicy::request_readiness(ordered_request);

    if (!ordered_readiness.is_deferred())
    {
        return 12;
    }

    return 0;
}

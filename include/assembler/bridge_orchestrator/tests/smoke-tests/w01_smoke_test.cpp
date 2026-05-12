#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/bridge_carriers/results/TBridgeCarrierResult.hpp"
#include "assembler/communication_context/bridge_carriers/errors/TBridgeCarrierError.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

int main()
{
    using namespace assembler::communication_context;

    constexpr auto token = TCorrelationToken::from_parts(1u, 2u);
    static_assert(token.is_valid(), "token should be valid");

    constexpr auto request = TPlacementRequest::make(token, "log_level_envelope", 128u, true);
    static_assert(request.is_valid(), "request should be valid");

    constexpr auto handle = TPlacementHandle::make(7u, token, "write_side_slot_family");
    static_assert(handle.is_valid(), "handle should be valid");

    constexpr auto readiness = TReadinessView::ready(token, 1u);
    static_assert(readiness.is_ready(), "readiness should be ready");

    constexpr auto admission = TAdmissionResult::accept(token);
    static_assert(admission.accepted(), "admission should be accepted");

    constexpr auto signal = TLoadSignal::completed(token, handle, 128u);
    static_assert(signal.completed(), "signal should be completed");

    constexpr auto next = TNextDestinationRequest::make(
        token,
        handle,
        TNextDestinationReason::continuous_flow_requested,
        "precalculate next placement");
    static_assert(next.is_valid(), "next destination request should be valid");

    constexpr auto result = TBridgeResult::success(token);
    static_assert(result.succeeded(), "bridge result should succeed");

    constexpr auto carrier_view = TCarrierView::make(TCarrierKind::placement_request, token, true, "request");
    static_assert(carrier_view.is_valid(), "carrier view should be valid");

    return 0;
}

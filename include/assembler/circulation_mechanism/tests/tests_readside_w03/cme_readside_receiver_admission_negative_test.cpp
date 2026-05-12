
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_admission_runtime.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    constexpr rscp::TPostBridgeCapacityProfile full_capacity{
        rscp::TPostBridgeCapacityProfileId::from_raw(1),
        rscp::TPostBridgeCapacityStatus::active,
        1U,
        1U,
        1U,
        1U,
        1U
    };

    constexpr rscp::TReceiverContextDescriptor receiver{
        rscp::TReceiverContextId::from_raw(2),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };

    constexpr rscp::TReadSideBackpressureProfile block_bp{
        rscp::TReadSideBackpressureProfileId::from_raw(3),
        rscp::TReadSideBackpressureMode::block_admission,
        rscp::TReadSideBackpressureState::pressure_detected,
        true
    };

    constexpr TReceiverBackpressureGate gate{
        TReceiverBackpressureGateId::from_raw(4),
        block_bp
    };

    constexpr TReceiverAdmissionController controller{
        TReceiverAdmissionControllerId::from_raw(5),
        gate
    };

    constexpr TReceiverAdmissionRequest request{
        TReceiverAdmissionRequestId::from_raw(6),
        TReceiverAdmissionRequestStatus::ready,
        full_capacity,
        receiver,
        rscp::TFailedDispatchKind::receiver_not_ready
    };

    constexpr auto decision = controller.decide(request);
    static_assert(!decision.accepted(), "admission rejected when no capacity/backpressure");
    static_assert(decision.decision == TReceiverAdmissionDecisionKind::reject_no_capacity, "no capacity rejection");

    constexpr rscp::TPostBridgeCapacityProfile enough_capacity{
        rscp::TPostBridgeCapacityProfileId::from_raw(10),
        rscp::TPostBridgeCapacityStatus::ready,
        2U,
        4U,
        1U,
        1U,
        0U
    };

    constexpr rscp::TReadSideBackpressureProfile retry_bp{
        rscp::TReadSideBackpressureProfileId::from_raw(11),
        rscp::TReadSideBackpressureMode::retry_pressure,
        rscp::TReadSideBackpressureState::pressure_detected,
        true
    };

    constexpr TReceiverAdmissionController retry_controller{
        TReceiverAdmissionControllerId::from_raw(12),
        TReceiverBackpressureGate{TReceiverBackpressureGateId::from_raw(13), retry_bp}
    };

    constexpr TReceiverAdmissionRequest retry_request{
        TReceiverAdmissionRequestId::from_raw(14),
        TReceiverAdmissionRequestStatus::ready,
        enough_capacity,
        receiver,
        rscp::TFailedDispatchKind::receiver_not_ready
    };

    constexpr auto retry_decision = retry_controller.decide(retry_request);
    static_assert(retry_decision.decision == TReceiverAdmissionDecisionKind::route_to_retry, "retry pressure routes to retry");

    return 0;
}

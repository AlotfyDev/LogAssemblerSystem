
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_admission_runtime.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    constexpr rscp::TPostBridgeCapacityProfile capacity{
        rscp::TPostBridgeCapacityProfileId::from_raw(1),
        rscp::TPostBridgeCapacityStatus::ready,
        2U,
        4U,
        2U,
        2U,
        1U
    };
    static_assert(capacity.receiver_has_room(), "capacity has room");

    constexpr rscp::TReceiverContextDescriptor receiver{
        rscp::TReceiverContextId::from_raw(2),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };

    constexpr rscp::TReadSideBackpressureProfile bp{
        rscp::TReadSideBackpressureProfileId::from_raw(3),
        rscp::TReadSideBackpressureMode::observe_only,
        rscp::TReadSideBackpressureState::normal,
        false
    };

    constexpr TReceiverBackpressureGate gate{
        TReceiverBackpressureGateId::from_raw(4),
        bp
    };
    static_assert(gate.is_valid(), "gate valid");
    static_assert(gate.evaluate(capacity) == TReceiverBackpressureGateStatus::ready, "gate ready");

    constexpr TReceiverAdmissionController controller{
        TReceiverAdmissionControllerId::from_raw(5),
        gate
    };

    constexpr TReceiverAdmissionRequest request{
        TReceiverAdmissionRequestId::from_raw(6),
        TReceiverAdmissionRequestStatus::ready,
        capacity,
        receiver,
        rscp::TFailedDispatchKind::none
    };

    constexpr auto decision = controller.decide(request);
    static_assert(decision.accepted(), "admission accepted");

    constexpr TReceiverAdmissionReport report{
        TReceiverAdmissionReportId::from_raw(7),
        decision,
        TReceiverAdmissionIssueKind::none
    };
    static_assert(report.passed(), "admission report passed");

    constexpr TReceiverAdmissionView view{
        TReceiverAdmissionControllerId::from_raw(5),
        decision
    };
    static_assert(view.accepted(), "view accepted");

    return 0;
}

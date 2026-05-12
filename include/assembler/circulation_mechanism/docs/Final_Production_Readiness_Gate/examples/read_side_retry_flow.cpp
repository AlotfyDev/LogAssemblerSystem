
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_engine.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_runtime_lists.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_admission_runtime.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_adapter_contracts.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/read_side_circulation_profile_w04.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

constexpr rscp::TReadSideAdmissionBoundaryDescriptor make_admission()
{
    return rscp::TReadSideAdmissionBoundaryDescriptor{
        rscp::TReadSideAdmissionBoundaryId::from_raw(1),
        rscp::TReadSideAdmissionMode::passive_pull_from_bridge,
        rscp::TReadSideAdmissionStatus::ready,
        true,
        false
    };
}

constexpr rscp::TReceiverContextDescriptor make_receiver()
{
    return rscp::TReceiverContextDescriptor{
        rscp::TReceiverContextId::from_raw(2),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };
}

constexpr rscp::TPostBridgeBoundaryContractDescriptor make_contract()
{
    return rscp::TPostBridgeBoundaryContractDescriptor{
        rscp::TPostBridgeBoundaryContractId::from_raw(3),
        rscp::TPostBridgeTransferSemantic::move,
        rscp::TPostBridgeBoundaryContractStatus::compatible,
        true,
        true
    };
}

constexpr rscp::TReadSideCirculationProfile make_read_profile()
{
    return rscp::TReadSideCirculationProfile{
        rscp::TReadSideProfileId::from_raw(4),
        rscp::TReadSideProfileStatus::ready,
        make_admission(),
        make_receiver(),
        make_contract()
    };
}

constexpr rscp::TPostBridgeCapacityProfile make_capacity(std::uint32_t current_load = 0U)
{
    return rscp::TPostBridgeCapacityProfile{
        rscp::TPostBridgeCapacityProfileId::from_raw(5),
        rscp::TPostBridgeCapacityStatus::ready,
        1U,
        4U,
        2U,
        2U,
        current_load
    };
}

constexpr rscp::TReadSideBackpressureProfile make_backpressure(
    rscp::TReadSideBackpressureMode mode,
    rscp::TReadSideBackpressureState state)
{
    return rscp::TReadSideBackpressureProfile{
        rscp::TReadSideBackpressureProfileId::from_raw(6),
        mode,
        state,
        true
    };
}

constexpr rscp::TDelayedReleaseProfile make_delayed_release()
{
    return rscp::TDelayedReleaseProfile{
        rscp::TDelayedReleaseProfileId::from_raw(7),
        rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
        true,
        10U
    };
}

constexpr rscp::TAddonBoundaryDescriptor make_addon()
{
    return rscp::TAddonBoundaryDescriptor{
        rscp::TAddonBoundaryId::from_raw(8),
        rscp::TAddonBoundaryKind::in_process_receiver,
        rscp::TAddonBoundaryStatus::ready,
        true,
        true,
        true,
        false
    };
}

constexpr TCirculationConfigurationDescriptor make_runtime_config()
{
    return TCirculationConfigurationDescriptor{
        TCirculationConfigurationId::from_raw(9),
        TCirculationConfigurationStatus::validated,
        TCirculationProfileKind::read_side,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };
}

int run_read_side_basic_flow()
{
    TReadSideCirculationConfig config{
        make_runtime_config(),
        make_read_profile(),
        make_capacity(0U),
        make_backpressure(rscp::TReadSideBackpressureMode::observe_only, rscp::TReadSideBackpressureState::normal),
        make_delayed_release(),
        make_addon()
    };

    if (!config.is_valid())
    {
        return 1;
    }

    TReadSideEngineProfile engine_profile{config, true, false};
    if (!engine_profile.is_valid())
    {
        return 2;
    }

    TReadSideCirculationEngine engine{TReadSideEngineId::from_raw(10), engine_profile};
    if (!engine.is_valid())
    {
        return 3;
    }

    if (!engine.initialize(TReadSideEngineReportId::from_raw(11)).passed())
    {
        return 4;
    }

    if (!engine.start(TReadSideEngineReportId::from_raw(12)).passed())
    {
        return 5;
    }

    TReceiverBackpressureGate gate{
        TReceiverBackpressureGateId::from_raw(13),
        config.backpressure_profile
    };

    TReceiverAdmissionController admission{
        TReceiverAdmissionControllerId::from_raw(14),
        gate
    };

    TReceiverAdmissionRequest request{
        TReceiverAdmissionRequestId::from_raw(15),
        TReceiverAdmissionRequestStatus::ready,
        config.capacity_profile,
        config.read_side_profile.receiver,
        rscp::TFailedDispatchKind::none
    };

    auto decision = admission.decide(request);
    if (!decision.accepted())
    {
        return 6;
    }

    auto receiver_adapter = TInProcessReceiverAdapterContract::make(
        TReadSideAdapterContractId::from_raw(16),
        TReadSideAdapterStatus::ready,
        false
    );

    auto adapter_result = receiver_adapter.evaluate(
        TReadSidePayloadRef::from_raw(100),
        TReadSideAdapterCapabilityKind::accept_payload,
        false
    );

    if (adapter_result != TReadSideAdapterInvocationStatus::accepted)
    {
        return 7;
    }

    rscp::TReceiverAcknowledgementRecord ack{
        rscp::TReceiverAcknowledgementId::from_raw(17),
        rscp::TReceiverAcknowledgementState::acknowledged
    };

    TReceiverAckWaitingList<2> ack_list{};
    if (!ack_list.push(ack).accepted())
    {
        return 8;
    }

    if (!ack_list.front() || !ack_list.front()->acknowledged())
    {
        return 9;
    }

    rscp::TDelayedReleaseRecord delayed{
        rscp::TDelayedReleaseRecordId::from_raw(18),
        rscp::TDelayedReleaseState::pending,
        rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
        0U
    };

    TDelayedReleaseList<2> delayed_list{};
    if (!delayed_list.push(delayed).accepted())
    {
        return 10;
    }

    if (!delayed_list.apply_profile_to_front(config.delayed_release_profile, true).accepted())
    {
        return 11;
    }

    if (!delayed_list.front() || delayed_list.front()->state != rscp::TDelayedReleaseState::released)
    {
        return 12;
    }

    if (!engine.stop(TReadSideEngineReportId::from_raw(19)).passed())
    {
        return 13;
    }

    return 0;
}

int run_read_side_retry_flow()
{
    rscp::TFailedDispatchRecord failed{
        rscp::TFailedDispatchId::from_raw(20),
        rscp::TFailedDispatchKind::receiver_not_ready,
        rscp::TFailedDispatchState::recorded,
        rscp::TReceiverAcknowledgementState::not_required,
        0U
    };

    TFailedDispatchWaitingList<2> failed_list{};
    if (!failed_list.push(failed).accepted())
    {
        return 20;
    }

    rscp::TReadSideRetryProfile retry_profile{
        rscp::TRetryProfileId::from_raw(21),
        rscp::TRetryPolicyKind::bounded_attempts,
        3U,
        false
    };

    rscp::TReceiverAcknowledgementRecord ack{
        rscp::TReceiverAcknowledgementId::from_raw(22),
        rscp::TReceiverAcknowledgementState::not_required
    };

    TRetryWaitingList<2> retry_list{};
    if (!retry_list.enqueue_from_failed_dispatch(
            failed,
            retry_profile,
            ack,
            rscp::TRetryAttemptId::from_raw(23)).accepted())
    {
        return 21;
    }

    if (!retry_list.front() || retry_list.front()->attempt_number != 1U)
    {
        return 22;
    }

    return 0;
}

int run_read_side_backpressure_flow()
{
    TReadSideCirculationConfig config{
        make_runtime_config(),
        make_read_profile(),
        make_capacity(4U),
        make_backpressure(rscp::TReadSideBackpressureMode::block_admission, rscp::TReadSideBackpressureState::pressure_detected),
        make_delayed_release(),
        make_addon()
    };

    TReceiverBackpressureGate gate{
        TReceiverBackpressureGateId::from_raw(30),
        config.backpressure_profile
    };

    TReceiverAdmissionController admission{
        TReceiverAdmissionControllerId::from_raw(31),
        gate
    };

    TReceiverAdmissionRequest request{
        TReceiverAdmissionRequestId::from_raw(32),
        TReceiverAdmissionRequestStatus::ready,
        config.capacity_profile,
        config.read_side_profile.receiver,
        rscp::TFailedDispatchKind::receiver_not_ready
    };

    auto decision = admission.decide(request);
    if (decision.accepted())
    {
        return 30;
    }

    if (decision.decision != TReceiverAdmissionDecisionKind::reject_no_capacity)
    {
        return 31;
    }

    rscp::TReadSideDiagnosticRecord diag{
        rscp::TReadSideDiagnosticId::from_raw(33),
        rscp::TReadSideDiagnosticKind::backpressure_active,
        rscp::TReadSideDiagnosticSeverity::error
    };

    auto report = rscp::TReadSideIntegrationReport::evaluate(
        rscp::TReadSideIntegrationReportId::from_raw(34),
        diag,
        make_addon()
    );

    if (report.passed())
    {
        return 32;
    }

    return 0;
}

int main()
{
    if (run_read_side_basic_flow() != 0) return 1;
    if (run_read_side_retry_flow() != 0) return 2;
    if (run_read_side_backpressure_flow() != 0) return 3;
    return 0;
}

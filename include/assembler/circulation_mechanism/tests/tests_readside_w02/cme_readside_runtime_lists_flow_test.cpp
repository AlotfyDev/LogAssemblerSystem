#include "assembler/circulation_mechanism/circulation_mechanism_read_side_runtime_lists.hpp"

using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    TFailedDispatchWaitingList<2> failed_list{};
    rscp::TFailedDispatchRecord failed{
        rscp::TFailedDispatchId::from_raw(1),
        rscp::TFailedDispatchKind::receiver_not_ready,
        rscp::TFailedDispatchState::recorded,
        rscp::TReceiverAcknowledgementState::not_required,
        0U
    };

    auto push_failed = failed_list.push(failed);
    if (!push_failed.accepted()) return 1;
    if (!failed_list.front() || !failed_list.front()->retry_candidate()) return 2;

    rscp::TReadSideRetryProfile retry_profile{
        rscp::TRetryProfileId::from_raw(2),
        rscp::TRetryPolicyKind::bounded_attempts,
        3U,
        false
    };

    rscp::TReceiverAcknowledgementRecord ack{
        rscp::TReceiverAcknowledgementId::from_raw(3),
        rscp::TReceiverAcknowledgementState::not_required
    };

    TRetryWaitingList<2> retry_list{};
    auto enqueue_retry = retry_list.enqueue_from_failed_dispatch(
        failed,
        retry_profile,
        ack,
        rscp::TRetryAttemptId::from_raw(4)
    );

    if (!enqueue_retry.accepted()) return 3;
    if (!retry_list.front() || retry_list.front()->attempt_number != 1U) return 4;

    rscp::TDelayedReleaseProfile delayed_profile{
        rscp::TDelayedReleaseProfileId::from_raw(5),
        rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
        true,
        10U
    };

    rscp::TDelayedReleaseRecord delayed{
        rscp::TDelayedReleaseRecordId::from_raw(6),
        rscp::TDelayedReleaseState::pending,
        rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
        0U
    };

    TDelayedReleaseList<2> delayed_list{};
    auto delayed_push = delayed_list.push(delayed);
    if (!delayed_push.accepted()) return 5;
    auto delayed_apply = delayed_list.apply_profile_to_front(delayed_profile, true);
    if (!delayed_apply.accepted()) return 6;
    if (!delayed_list.front() || delayed_list.front()->state != rscp::TDelayedReleaseState::released) return 7;

    TReceiverAckWaitingList<2> ack_list{};
    auto ack_push = ack_list.push(rscp::TReceiverAcknowledgementRecord{
        rscp::TReceiverAcknowledgementId::from_raw(7),
        rscp::TReceiverAcknowledgementState::acknowledged
    });
    if (!ack_push.accepted()) return 8;
    if (!ack_list.front() || !ack_list.front()->acknowledged()) return 9;

    TReadSideRuntimeListsView view{
        failed_list.size(),
        retry_list.size(),
        delayed_list.size(),
        ack_list.size()
    };
    if (!view.has_pending_work()) return 10;

    return 0;
}

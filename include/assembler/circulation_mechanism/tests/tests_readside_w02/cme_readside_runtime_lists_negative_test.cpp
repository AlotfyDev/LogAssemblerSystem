#include "assembler/circulation_mechanism/circulation_mechanism_read_side_runtime_lists.hpp"

using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    TFailedDispatchWaitingList<1> failed_list{};

    auto invalid = failed_list.push(rscp::TFailedDispatchRecord{});
    if (!invalid.rejected()) return 1;

    rscp::TFailedDispatchRecord terminal{
        rscp::TFailedDispatchId::from_raw(1),
        rscp::TFailedDispatchKind::receiver_not_ready,
        rscp::TFailedDispatchState::resolved,
        rscp::TReceiverAcknowledgementState::acknowledged,
        0U
    };

    auto terminal_push = failed_list.push(terminal);
    if (!terminal_push.rejected()) return 2;

    rscp::TFailedDispatchRecord retryable{
        rscp::TFailedDispatchId::from_raw(2),
        rscp::TFailedDispatchKind::receiver_not_ready,
        rscp::TFailedDispatchState::recorded,
        rscp::TReceiverAcknowledgementState::not_required,
        0U
    };

    auto accepted = failed_list.push(retryable);
    if (!accepted.accepted()) return 3;

    auto duplicate = failed_list.push(retryable);
    if (!duplicate.rejected()) return 4;

    TRetryWaitingList<1> retry_list{};
    rscp::TReadSideRetryProfile disabled{
        rscp::TRetryProfileId::from_raw(3),
        rscp::TRetryPolicyKind::disabled,
        0U,
        false
    };

    auto enqueue = retry_list.enqueue_from_failed_dispatch(
        retryable,
        disabled,
        rscp::TReceiverAcknowledgementRecord{rscp::TReceiverAcknowledgementId::from_raw(4), rscp::TReceiverAcknowledgementState::not_required},
        rscp::TRetryAttemptId::from_raw(5)
    );
    if (!enqueue.rejected()) return 5;

    TDelayedReleaseList<1> delayed_list{};
    auto not_pending = delayed_list.push(rscp::TDelayedReleaseRecord{
        rscp::TDelayedReleaseRecordId::from_raw(6),
        rscp::TDelayedReleaseState::released,
        rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
        0U
    });
    if (!not_pending.rejected()) return 6;

    return 0;
}

#include "cme_benchmark_common.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_read_side_runtime_lists.hpp"

using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main() {
    volatile std::uint64_t sink = 0;
    auto result = cme_bench::run("read_side_retry_pressure", 30000, [&](std::uint64_t i) {
        TFailedDispatchWaitingList<4> failed{};
        TRetryWaitingList<4> retry{};
        rscp::TFailedDispatchRecord record{
            rscp::TFailedDispatchId::from_raw(i + 1),
            rscp::TFailedDispatchKind::receiver_not_ready,
            rscp::TFailedDispatchState::recorded,
            rscp::TReceiverAcknowledgementState::not_required,
            0
        };
        failed.push(record);
        retry.enqueue_from_failed_dispatch(
            record,
            rscp::TReadSideRetryProfile{rscp::TRetryProfileId::from_raw(1), rscp::TRetryPolicyKind::bounded_attempts, 3, false},
            rscp::TReceiverAcknowledgementRecord{rscp::TReceiverAcknowledgementId::from_raw(1), rscp::TReceiverAcknowledgementState::not_required},
            rscp::TRetryAttemptId::from_raw(i + 1)
        );
        sink += retry.size();
    });
    result.print();
    return sink == 0 ? 1 : 0;
}

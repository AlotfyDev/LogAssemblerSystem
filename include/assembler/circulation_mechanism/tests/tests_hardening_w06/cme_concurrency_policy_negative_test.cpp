#include "assembler/circulation_mechanism/circulation_mechanism_concurrency.hpp"

using namespace assembler::circulation_mechanism::concurrency;

int main()
{
    constexpr TCirculationConcurrencyProfile multi_writer{
        TCirculationConcurrencyProfileId::from_raw(1),
        TCirculationConcurrencyMode::single_writer_independent_instances,
        TCirculationMutationAuthorityKind::single_writer,
        TCirculationThreadingGuaranteeSet{true, true, true, true, true, true},
        true,
        false,
        false,
        false,
        false,
        false,
        false
    };
    static_assert(!multi_writer.accepted(), "multi-writer request rejected");
    static_assert(multi_writer.validation_issue() == TCirculationConcurrencyIssueKind::multi_writer_requested, "multi writer issue");

    constexpr TCirculationConcurrencyProfile internal_threads{
        TCirculationConcurrencyProfileId::from_raw(2),
        TCirculationConcurrencyMode::single_writer_independent_instances,
        TCirculationMutationAuthorityKind::single_writer,
        TCirculationThreadingGuaranteeSet{true, true, true, true, true, true},
        false,
        false,
        true,
        false,
        false,
        false,
        false
    };
    static_assert(!internal_threads.accepted(), "internal threading request rejected");
    static_assert(internal_threads.validation_issue() == TCirculationConcurrencyIssueKind::internal_threading_requested, "internal threading issue");

    constexpr TCirculationConcurrencyProfile bridge_leak{
        TCirculationConcurrencyProfileId::from_raw(3),
        TCirculationConcurrencyMode::single_writer_independent_instances,
        TCirculationMutationAuthorityKind::single_writer,
        TCirculationThreadingGuaranteeSet{true, true, true, true, true, true},
        false,
        false,
        false,
        false,
        false,
        true,
        false
    };
    static_assert(!bridge_leak.accepted(), "bridge runtime leak rejected");
    static_assert(bridge_leak.validation_issue() == TCirculationConcurrencyIssueKind::bridge_runtime_leak, "bridge leak issue");

    return 0;
}

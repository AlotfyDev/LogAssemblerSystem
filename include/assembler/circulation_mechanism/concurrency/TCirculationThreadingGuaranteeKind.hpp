#pragma once
    #include <cstdint>

    /*
        TCirculationThreadingGuaranteeKind.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Responsibility:
            Classifies threading/concurrency guarantees.

        Explicit non-ownership:
            - Does not implement OS thread management.
            - Does not implement a worker pool.
            - Does not implement a scheduler.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    enum class TCirculationThreadingGuaranteeKind : std::uint8_t {
        no_internal_threads, no_scheduler, no_shared_mutable_state_by_default, independent_instances, external_synchronization_required, bounded_parallelism_requires_policy
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

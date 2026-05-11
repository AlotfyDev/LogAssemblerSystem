#pragma once
    #include <cstdint>

    /*
        TCirculationConcurrencyMode.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Responsibility:
            Classifies the allowed concurrency model.

        Explicit non-ownership:
            - Does not implement OS thread management.
            - Does not implement a worker pool.
            - Does not implement a scheduler.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    enum class TCirculationConcurrencyMode : std::uint8_t {
        single_writer_single_instance, single_writer_independent_instances, bounded_internal_parallelism_declared, external_scheduler_owned, diagnostic_only
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

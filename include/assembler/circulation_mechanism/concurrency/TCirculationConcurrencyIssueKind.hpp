#pragma once
    #include <cstdint>

    /*
        TCirculationConcurrencyIssueKind.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Responsibility:
            Classifies concurrency policy violations.

        Explicit non-ownership:
            - Does not implement OS thread management.
            - Does not implement a worker pool.
            - Does not implement a scheduler.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    enum class TCirculationConcurrencyIssueKind : std::uint8_t {
        none, invalid_profile_id, multi_writer_requested, shared_mutable_state_requested, internal_threading_requested, scheduler_ownership_requested, unbounded_parallelism_requested, bridge_runtime_leak, receiver_runtime_leak
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

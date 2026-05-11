#pragma once
    #include <cstdint>

    /*
        TCirculationMutationAuthorityKind.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Responsibility:
            Classifies mutation authority.

        Explicit non-ownership:
            - Does not implement OS thread management.
            - Does not implement a worker pool.
            - Does not implement a scheduler.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    enum class TCirculationMutationAuthorityKind : std::uint8_t {
        single_writer, component_local_owner, read_only_observer, external_owner, forbidden
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

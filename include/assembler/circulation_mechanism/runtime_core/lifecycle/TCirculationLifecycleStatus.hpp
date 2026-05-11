#pragma once
    #include <cstdint>

    /*
        TCirculationLifecycleStatus.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Shared lifecycle status vocabulary for circulation runtime surfaces.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationLifecycleStatus : std::uint8_t {
        unconfigured,
        configured,
        constructed,
        initialized,
        running,
        draining,
        releasing,
        recycling,
        stopped,
        faulted
    };
    } // namespace circulation_mechanism
} // namespace assembler

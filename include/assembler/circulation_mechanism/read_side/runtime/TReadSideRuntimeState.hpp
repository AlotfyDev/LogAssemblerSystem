#pragma once
    #include <cstdint>

    /*
        TReadSideRuntimeState.hpp

        Delivery:
            CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

        Responsibility:
            ReadSide-specific runtime state.

        Explicit non-ownership:
            - Does not execute PreBridge behavior.
            - Does not execute Bridge Orchestrator behavior.
            - Does not implement receiver/addon behavior.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideRuntimeState : std::uint8_t {
        unconfigured, configured, initialized, ready, running, draining, stopped, faulted
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

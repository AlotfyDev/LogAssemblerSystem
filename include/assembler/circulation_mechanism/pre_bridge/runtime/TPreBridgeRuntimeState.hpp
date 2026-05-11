#pragma once
    #include <cstdint>

    /*
        TPreBridgeRuntimeState.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W01 — PreBridge Engine Facade And Injection Surface

        Responsibility:
            PreBridge-specific runtime state.

        Explicit non-ownership:
            - Does not execute ReadSide behavior.
            - Does not execute bridge protocol.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

    enum class TPreBridgeRuntimeState : std::uint8_t {
        unconfigured, configured, initialized, ready, running, draining, stopped, faulted
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

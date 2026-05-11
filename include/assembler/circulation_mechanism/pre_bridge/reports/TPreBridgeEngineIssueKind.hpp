#pragma once
    #include <cstdint>

    /*
        TPreBridgeEngineIssueKind.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W01 — PreBridge Engine Facade And Injection Surface

        Responsibility:
            PreBridge engine issue classification.

        Explicit non-ownership:
            - Does not execute ReadSide behavior.
            - Does not execute bridge protocol.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

    enum class TPreBridgeEngineIssueKind : std::uint8_t {
        none, invalid_engine_id, invalid_configuration, invalid_capacity, boundary_not_ready, reference_supply_not_ready, ingress_not_ready, dispatcher_not_ready, runtime_not_initialized, read_side_dependency_detected
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

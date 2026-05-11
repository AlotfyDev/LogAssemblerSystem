#pragma once
    #include <cstdint>

    /*
        TReadSideEngineIssueKind.hpp

        Delivery:
            CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

        Responsibility:
            ReadSide engine issue classification.

        Explicit non-ownership:
            - Does not execute PreBridge behavior.
            - Does not execute Bridge Orchestrator behavior.
            - Does not implement receiver/addon behavior.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideEngineIssueKind : std::uint8_t {
        none, invalid_engine_id, invalid_configuration, invalid_read_side_profile, invalid_boundary_contract, receiver_context_not_ready, addon_boundary_not_ready, runtime_not_initialized, pre_bridge_dependency_detected
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
    #include <cstdint>

    /*
        TPostBridgeBoundaryContractStatus.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines post-bridge boundary contract status.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TPostBridgeBoundaryContractStatus : std::uint8_t {
        undefined,
        declared,
        compatible,
        incompatible,
        requires_review,
        blocked
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

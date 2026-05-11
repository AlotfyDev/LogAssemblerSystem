#pragma once
    #include <cstdint>

    /*
        TReadSideAdmissionStatus.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines read-side admission boundary status.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideAdmissionStatus : std::uint8_t {
        unbound,
        bound,
        ready,
        blocked,
        mismatch,
        closed
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
    #include <cstdint>

    /*
        TReadSideProfileStatus.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines lifecycle/readiness status for a read-side circulation profile.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideProfileStatus : std::uint8_t {
        undefined,
        draft,
        ready,
        active,
        blocked_by_boundary,
        blocked_by_receiver,
        deferred
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

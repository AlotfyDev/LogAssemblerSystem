#pragma once
    #include <cstdint>

    /*
        TCapacityProfileStatus.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines lifecycle status of a capacity profile.

        Explicit non-ownership:
            - Does not execute scaling.
            - Does not allocate or mutate containers.
            - Does not handle bridge/read-side backpressure.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TCapacityProfileStatus : std::uint8_t
    {
        undefined,
        draft,
        active,
        switch_pending,
        deprecated,
        invalid
    };
    } // namespace circulation_mechanism
} // namespace assembler

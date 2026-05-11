#pragma once
    #include <cstdint>

    /*
        TScalingDirectionKind.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines scaling direction categories.

        Explicit non-ownership:
            - Does not execute scaling.
            - Does not allocate or mutate containers.
            - Does not handle bridge/read-side backpressure.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TScalingDirectionKind : std::uint8_t
    {
        none,
        horizontal,
        vertical,
        mixed
    };
    } // namespace circulation_mechanism
} // namespace assembler

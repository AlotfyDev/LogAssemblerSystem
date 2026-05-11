#pragma once
    #include <cstdint>

    /*
        TCapacityProfileKind.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines capacity profile kind.

        Explicit non-ownership:
            - Does not execute scaling.
            - Does not allocate or mutate containers.
            - Does not handle bridge/read-side backpressure.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TCapacityProfileKind : std::uint8_t
    {
        circulation,
        uniform_container,
        ingress,
        dispatch,
        waiting_list,
        reference_supply,
        extreme_default
    };
    } // namespace circulation_mechanism
} // namespace assembler

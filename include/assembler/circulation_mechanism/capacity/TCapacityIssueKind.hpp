#pragma once
    #include <cstdint>

    /*
        TCapacityIssueKind.hpp

        Delivery:
            CME-CAPACITY-PROD-W01 — Production Profile And Scaling Contract

        Current responsibility:
            Defines capacity/profile diagnostic issue kinds.

        Explicit non-ownership:
            - Does not execute scaling.
            - Does not allocate or mutate containers.
            - Does not handle bridge/read-side backpressure.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TCapacityIssueKind : std::uint8_t
    {
        none,
        invalid_profile_id,
        invalid_generation_id,
        invalid_container_count,
        invalid_slot_count,
        invalid_payload_capacity,
        invalid_ingress_capacity,
        invalid_dispatch_capacity,
        non_uniform_container_capacity,
        slot_layout_mismatch,
        waiting_list_capacity_exceeded,
        reference_supply_depth_insufficient,
        extreme_profile_insufficient,
        unsafe_profile_switch,
        overflow_risk
    };
    } // namespace circulation_mechanism
} // namespace assembler

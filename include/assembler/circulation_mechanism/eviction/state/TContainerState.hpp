#pragma once
    #include <cstdint>
    /*
        TContainerState.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Container state dependency for eviction eligibility.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TContainerState : std::uint8_t {
        default_empty, ingress_ready, ingress_round_member, receiving, filled_or_closed, dispatch_candidate, dispatch_round_member, dispatch_exposed, dispatch_completed, reset_pending, under_moderation, inactive, evicted, faulted
    };
    } // namespace circulation_mechanism
} // namespace assembler

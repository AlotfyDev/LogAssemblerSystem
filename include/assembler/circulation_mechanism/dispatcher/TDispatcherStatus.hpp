#pragma once
    #include <cstdint>
    /*
        TDispatcherStatus.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Dispatcher lifecycle/status.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatcherStatus : std::uint8_t {
        uninitialized, ready, awaiting_dispatch_ref, exposing, passive_exposed, boundary_observed, boundary_consumed, release_pending, closed, boundary_assumption_broken
    };
    } // namespace circulation_mechanism
} // namespace assembler

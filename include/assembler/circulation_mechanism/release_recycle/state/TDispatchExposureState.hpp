#pragma once
    #include <cstdint>
    /*
        TDispatchExposureState.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Dispatch exposure state dependency.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatchExposureState : std::uint8_t {
        ready, awaiting_dispatch_ref, exposing, passive_exposed, bridge_observed, bridge_consumed, release_pending, closed, boundary_assumption_broken
    };
    } // namespace circulation_mechanism
} // namespace assembler

#pragma once
    #include <cstdint>
    /*
        TBridgeFacingBoundaryStatus.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Bridge-facing boundary status.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TBridgeFacingBoundaryStatus : std::uint8_t {
        undefined, declared, ready, blocked, mismatch, closed
    };
    } // namespace circulation_mechanism
} // namespace assembler

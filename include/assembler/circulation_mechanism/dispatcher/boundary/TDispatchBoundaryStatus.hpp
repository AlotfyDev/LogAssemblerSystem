#pragma once
    #include <cstdint>
    /*
        TDispatchBoundaryStatus.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Dispatch boundary status.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatchBoundaryStatus : std::uint8_t {
        unbound, bound, ready, exposed, observed, consumed, mismatch, closed, assumption_broken
    };
    } // namespace circulation_mechanism
} // namespace assembler

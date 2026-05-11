#pragma once
    #include <cstdint>
    /*
        TSafePointState.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Safe-point state dependency for eviction guard.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TSafePointState : std::uint8_t {
        unavailable, pending, available, claimed, consumed, expired, violated
    };
    } // namespace circulation_mechanism
} // namespace assembler

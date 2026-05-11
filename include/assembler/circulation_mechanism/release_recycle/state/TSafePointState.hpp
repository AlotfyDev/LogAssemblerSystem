#pragma once
    #include <cstdint>
    /*
        TSafePointState.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Safe-point state dependency.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TSafePointState : std::uint8_t {
        unavailable, pending, available, claimed, consumed, expired, violated
    };
    } // namespace circulation_mechanism
} // namespace assembler

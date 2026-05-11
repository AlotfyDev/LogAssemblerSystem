#pragma once
    #include <cstdint>
    /*
        TReferenceValidityState.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Reference validity state dependency.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TReferenceValidityState : std::uint8_t {
        prepared, issued, consumed, expired, invalidated, stale_detected, blocked_by_state
    };
    } // namespace circulation_mechanism
} // namespace assembler

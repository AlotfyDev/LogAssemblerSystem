#pragma once
    #include <cstdint>
    /*
        TRoundState.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Round state dependency.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TRoundState : std::uint8_t {
        idle, collecting_candidates, open, locked, draining, closing, closed, completed, aborted, invariant_violation
    };
    } // namespace circulation_mechanism
} // namespace assembler

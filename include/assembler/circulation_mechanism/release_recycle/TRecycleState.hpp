#pragma once
    #include <cstdint>
    /*
        TRecycleState.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Defines release/recycle lifecycle state.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TRecycleState : std::uint8_t {
        not_recyclable, release_pending, released, recyclable, reset_pending, under_moderation, default_empty, reentry_eligible, blocked, faulted
    };
    } // namespace circulation_mechanism
} // namespace assembler

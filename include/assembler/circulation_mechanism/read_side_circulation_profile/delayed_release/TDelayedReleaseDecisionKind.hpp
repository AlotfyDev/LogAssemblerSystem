#pragma once
    #include <cstdint>

    /*
        TDelayedReleaseDecisionKind.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Decision produced by delayed release profile.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TDelayedReleaseDecisionKind : std::uint8_t {
        release_now, wait_for_trigger, blocked, expired, manual_review_required, not_applicable
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

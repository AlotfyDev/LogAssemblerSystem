#pragma once
    #include <cstdint>
    /*
        TReleaseRecycleStatus.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Classifies release/recycle operation result.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TReleaseRecycleStatus : std::uint8_t {
        not_attempted, accepted, rejected_invalid_id, rejected_missing_safe_point, rejected_invalid_transition, rejected_active_reference, rejected_active_exposure, rejected_not_releasable, rejected_not_recyclable, rejected_not_resettable, rejected_not_reentry_eligible
    };
    } // namespace circulation_mechanism
} // namespace assembler

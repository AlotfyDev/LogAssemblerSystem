#pragma once
    #include <cstdint>
    /*
        TEvictionEvaluationStatus.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Eviction candidate evaluation result.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TEvictionEvaluationStatus : std::uint8_t {
        not_attempted, accepted, rejected_invalid_candidate, rejected_no_safe_point, rejected_active_ingress, rejected_active_dispatch, rejected_active_round, rejected_active_refs, rejected_invalid_time_range, delegated_to_read_side, disabled_by_profile
    };
    } // namespace circulation_mechanism
} // namespace assembler

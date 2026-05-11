#pragma once
    #include <cstdint>
    /*
        TEvictionCandidateStatus.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Eviction candidate lifecycle/evaluation status.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TEvictionCandidateStatus : std::uint8_t {
        not_evaluated, eligible, rejected_active_ingress, rejected_active_dispatch, rejected_round_member, rejected_active_refs, rejected_no_safe_point, rejected_invalid_time_range, selected, applied, delegated_to_read_side
    };
    } // namespace circulation_mechanism
} // namespace assembler

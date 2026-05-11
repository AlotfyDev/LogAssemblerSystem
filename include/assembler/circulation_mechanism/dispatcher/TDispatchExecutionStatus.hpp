#pragma once
    #include <cstdint>
    /*
        TDispatchExecutionStatus.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Dispatcher exposure execution result.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatchExecutionStatus : std::uint8_t {
        not_attempted, accepted, rejected_invalid_dispatcher, rejected_closed, rejected_invalid_ref, rejected_wrong_ref_direction, rejected_boundary_mismatch, rejected_target_failed, rejected_push_disabled, boundary_assumption_broken
    };
    } // namespace circulation_mechanism
} // namespace assembler

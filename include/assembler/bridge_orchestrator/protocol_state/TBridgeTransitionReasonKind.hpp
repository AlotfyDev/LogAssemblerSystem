#pragma once

/**
 * @file TBridgeTransitionReasonKind.hpp
 * @brief Canonical vocabulary for transition causality and diagnostics.
 *
 * Architectural Role:
 *
 *     Semantic classifier for runtime events.
 *
 * This entity categorizes WHY a transition occurred or was rejected,
 * enabling diagnostics-grade observability without coupling to 
 * specific implementation details.
 */

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Classified reasons for protocol state transitions.
 *
 * Categories:
 * - Natural Progression (Expected lifecycle flow)
 * - Operational Intervention (Manual/System triggers)
 * - Admission Rejection (Legality violations)
 * - Invariant Violation (Safety breaches)
 * - System Errors (Unexpected failures)
 */
enum class TTransitionReasonKind : std::uint8_t
{
    // === Natural Progression ===
    Unspecified = 0,
    
    Lifecycle_Forward_Progression,   // Normal stage advance
    Lifecycle_Completion,            // Reached terminal state naturally
    
    // === Operational Intervention ===
    Operator_Requested,              // Explicit user/admin trigger
    System_Recovery,                 // Auto-healing mechanism
    Pipeline_Orchestration,          // Driven by external pipeline step
    
    // === Admission Rejection (Legality) ===
    Illegal_Transition_Sequence,     // Violates StageTransitionMatrix
    Invalid_Source_State,            // Current state mismatch
    Invalid_Target_State,            // Target state undefined/blocked
    
    // === Invariant Violation (Safety) ===
    Continuity_Break,                // Snapshot chain broken
    Generation_Reggression,          // Time-travel attempt detected
    Terminal_State_Mutation,         // Attempt to modify terminal state
    
    // === System Errors ===
    Internal_Engine_Failure,         // Unexpected logic error
    Resource_Unavailable             // Required resource missing
};

/**
 * @brief Checks if reason represents a successful/natural progression.
 */
[[nodiscard]] constexpr bool 
is_natural_progression(TTransitionReasonKind kind) noexcept
{
    return kind == TTransitionReasonKind::Lifecycle_Forward_Progression ||
           kind == TTransitionReasonKind::Lifecycle_Completion;
}

/**
 * @brief Checks if reason represents an operational intervention.
 */
[[nodiscard]] constexpr bool 
is_operational_intervention(TTransitionReasonKind kind) noexcept
{
    return kind == TTransitionReasonKind::Operator_Requested ||
           kind == TTransitionReasonKind::System_Recovery ||
           kind == TTransitionReasonKind::Pipeline_Orchestration;
}

/**
 * @brief Checks if reason represents a rejection or failure.
 */
[[nodiscard]] constexpr bool 
is_rejection_or_failure(TTransitionReasonKind kind) noexcept
{
    return kind >= TTransitionReasonKind::Illegal_Transition_Sequence;
}

/**
 * @brief Checks if reason indicates a critical safety violation.
 */
[[nodiscard]] constexpr bool 
is_safety_violation(TTransitionReasonKind kind) noexcept
{
    return kind == TTransitionReasonKind::Continuity_Break ||
           kind == TTransitionReasonKind::Generation_Reggression ||
           kind == TTransitionReasonKind::Terminal_State_Mutation;
}

} // namespace assembler::bridge_orchestrator::protocol_state

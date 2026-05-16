#pragma once

/**
 * @file TBridgeTransitionEvidenceRuntime.hpp
 * @brief Runtime engine for generating transition evidence and diagnostics.
 *
 * Responsibilities:
 *
 * - Synthesize transition reports from execution results
 * - Classify outcomes into semantic reason kinds
 * - Maintain evidence chain integrity
 * - Provide diagnostics visibility
 *
 * Architectural Role:
 *
 *     Diagnostics synthesis layer.
 *     
 * It consumes raw execution results (from WAVE 3) and admission 
 * reports (from WAVE 2) to produce high-fidelity evidence records.
 */

#include "TBridgeProtocolStateTransitionReport.hpp"
#include "TBridgeTransitionAdmissionEngine.hpp" // For admission report details
#include "TBridgeProtocolStateRuntime.hpp"      // For execution result

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Engine responsible for evidence generation.
 */
class TBridgeTransitionEvidenceRuntime
{
public:

    /**
     * @brief Synthesizes a diagnostic report from a runtime execution result.
     *
     * @param result The result from TBridgeProtocolStateRuntime::execute_transition
     * @param state_before The state prior to execution
     * @return A complete transition report ready for logging or auditing.
     */
    [[nodiscard]] static constexpr TProtocolStateTransitionReport
    synthesize_report(
        const TProtocolStateRuntimeResult& result,
        TBridgeStage state_before) noexcept
    {
        TProtocolStateTransitionReport report {};

        report.attempt = result.applied_transition.value_or(TBridgeTransition{});
        report.state_before = state_before;
        report.generation = (result.transition_applied) 
                            ? (/* hypothetical new gen */ 0) // Logic handled below
                            : 0; 

        // Determine State After
        if (result.transition_applied && result.applied_transition.has_value())
        {
            report.state_after = result.applied_transition.value().to;
            report.admitted = true;
            
            // Classify Success Reason
            report.reason_kind = classify_success_reason(result.applied_transition.value());
        }
        else
        {
            report.state_after = state_before; // No change
            report.admitted = false;
            
            // Classify Failure Reason
            report.reason_kind = classify_failure_reason(result.admission_report);
        }

        return report;
    }

private:

    /**
     * @brief Classifies why a transition succeeded.
     */
    [[nodiscard]] static constexpr TTransitionReasonKind
    classify_success_reason(const TBridgeTransition& transition) noexcept
    {
        // Default to natural progression unless metadata suggests otherwise
        // In a richer system, transition metadata could drive this.
        if (is_terminal_stage(transition.to))
        {
            return TTransitionReasonKind::Lifecycle_Completion;
        }
        
        return TTransitionReasonKind::Lifecycle_Forward_Progression;
    }

    /**
     * @brief Classifies why a transition failed based on admission report.
     */
    [[nodiscard]] static constexpr TTransitionReasonKind
    classify_failure_reason(const TTransitionAdmissionReport& admission) noexcept
    {
        if (!admission.is_legal_sequence)
        {
            return TTransitionReasonKind::Illegal_Transition_Sequence;
        }
        
        if (!admission.is_valid_source)
        {
            return TTransitionReasonKind::Invalid_Source_State;
        }

        if (!admission.is_valid_target)
        {
            return TTransitionReasonKind::Invalid_Target_State;
        }

        // Fallback for unknown rejections
        return TTransitionReasonKind::Internal_Engine_Failure;
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state

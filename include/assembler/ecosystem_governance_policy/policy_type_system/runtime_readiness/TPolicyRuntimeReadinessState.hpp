#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeReadinessState.hpp

 * Wave: EG-POL-W19_Runtime_Readiness_Model
 * Domain: ecosystem_governance / policy_type_system / runtime_readiness
 *
 * Architectural boundary:
 *   W19 implements the Runtime Readiness Model that follows W18 Realization
 *   Contract Foundation. It is derived from EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness
 *   and guarded by EG-POL-ARCH-008_Compliance_And_Validation_Matrix. Runtime
 *   readiness is a pre-execution gate: it determines whether a policy assignment
 *   and target context are sufficiently prepared for later realization planning
 *   or controlled realizer invocation. It is not runtime execution, not target
 *   invocation, not target mutation, not material circulation, not communication
 *   binding, and not add-on execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity, family, version, scope, source, issue, and result vocabulary.
 *   - W06 supplies target-kind and realization-binding descriptors while preserving descriptor-only semantics.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies policy-family and scope foundations.
 *   - W13 supplies target-capability contracts.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict states.
 *   - W16 and W17 supply policy source/publication and registry-versioning views.
 *   - W18 supplies realization contracts, realization contexts, requests, preconditions, failures, and traces.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W19 implements the runtime-ready portion of that chain. A positive readiness
 *   report allows later realization planning to be considered; it does not perform
 *   realization. A readiness evaluator consumes descriptive artifacts and reports
 *   readiness status without invoking targets or changing runtime state.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyRealizer, TPolicyExecutor, runtime
 *   execution engine, target invocation, target mutation, material circulation
 *   behavior, communication binding, add-on execution, source parsing,
 *   persistent registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a compact set of value carriers
 *   and structural helpers.
 * File responsibility:
 *   TPolicyRuntimeReadinessState defines the governed readiness states used to
 *   separate not evaluated, pending, ready, conditionally ready, not ready,
 *   blocked, forbidden, and quarantined conditions. These states describe the
 *   result of pre-execution readiness evaluation only; none of them executes
 *   policy behavior.
 */

enum class TPolicyRuntimeReadinessState : std::uint8_t
{
    unknown = 0,
    not_evaluated = 1,
    readiness_pending = 2,
    runtime_ready = 3,
    runtime_ready_with_warnings = 4,
    conditionally_ready = 5,
    not_ready = 6,
    blocked = 7,
    deferred = 8,
    forbidden = 9,
    quarantined = 10
};

[[nodiscard]] constexpr bool IsPositive(TPolicyRuntimeReadinessState state) noexcept
{
    return state == TPolicyRuntimeReadinessState::runtime_ready ||
           state == TPolicyRuntimeReadinessState::runtime_ready_with_warnings ||
           state == TPolicyRuntimeReadinessState::conditionally_ready;
}

[[nodiscard]] constexpr bool IsBlocking(TPolicyRuntimeReadinessState state) noexcept
{
    return state == TPolicyRuntimeReadinessState::not_ready ||
           state == TPolicyRuntimeReadinessState::blocked ||
           state == TPolicyRuntimeReadinessState::forbidden ||
           state == TPolicyRuntimeReadinessState::quarantined;
}

[[nodiscard]] constexpr bool MayProceedToRealizationPlanning(TPolicyRuntimeReadinessState state) noexcept
{
    return state == TPolicyRuntimeReadinessState::runtime_ready ||
           state == TPolicyRuntimeReadinessState::runtime_ready_with_warnings ||
           state == TPolicyRuntimeReadinessState::conditionally_ready;
}


} // namespace assembler::ecosystem_governance::policy_type_system

#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W21_PolicyRealizer_Interface_And_Result_Model
 * Domain: ecosystem_governance / policy_type_system / policy_realizer
 *
 * Architectural boundary:
 *   W21 opens Phase D — Policy Realization Runtime by introducing the
 *   PolicyRealizer interface and result vocabulary. This is the first wave
 *   allowed to name TPolicyRealizer, but it is still an interface-and-result
 *   model, not a concrete execution engine. It consumes the pre-execution
 *   artifacts produced by W18, W19, and W20: realization contracts,
 *   realization contexts and requests, runtime readiness reports, and runtime
 *   plans. The realizer interface may declare the shape of a future runtime
 *   boundary, but this wave does not invoke targets, mutate runtime components,
 *   schedule execution, perform material circulation, bind communication
 *   endpoints, or execute add-ons.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive identity and policy source/version/scope vocabulary.
 *   - W06 supplies realization binding and target-kind descriptors while
 *     preserving descriptor-only semantics.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 and W13 supply policy-family/scope and target-capability foundations.
 *   - W14 supplies family-target compatibility rules and reports.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16 and W17 supply source/publication and registry-versioning views.
 *   - W18 supplies realization contracts, contexts, requests, failures, and traces.
 *   - W19 supplies runtime readiness gates, issues, reports, and evaluator vocabulary.
 *   - W20 supplies the pre-execution runtime plan consumed by this interface.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W21 sits after runtime plan creation and begins the interface surface for a
 *   future realizer. It preserves the rule that Realization Contract != Realizer
 *   and Runtime Readiness != Runtime Execution. A W21 result may describe that
 *   a realizer accepted, rejected, deferred, or inspected a plan; it must not
 *   claim downstream success or direct target mutation.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, a runtime execution engine,
 *   target invocation, target mutation, material circulation behavior,
 *   communication binding, add-on execution, source parsing, persistent registry
 *   storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a compact set of value carriers,
 *   enum vocabularies, and interface declarations.
 */
/*
 * File responsibility:
 *   TPolicyRealizerCapability describes what a realizer interface participant
 *   claims to support. A capability is descriptive and must not be interpreted
 *   as a method call, target handle, or permission to execute runtime behavior.
 */
enum class TPolicyRealizerCapability : std::uint8_t
{
    unknown = 0,
    accepts_runtime_plan = 1,
    consumes_readiness_report = 2,
    supports_dry_run = 3,
    supports_configuration_realization = 4,
    supports_lifecycle_realization = 5,
    supports_replacement_realization = 6,
    supports_runtime_capable_realization = 7,
    supports_rollback_preparation = 8,
    produces_realization_trace = 9,
    produces_result_report = 10
};

[[nodiscard]] constexpr bool IsRuntimeAffecting(TPolicyRealizerCapability capability) noexcept
{
    return capability == TPolicyRealizerCapability::supports_configuration_realization ||
           capability == TPolicyRealizerCapability::supports_lifecycle_realization ||
           capability == TPolicyRealizerCapability::supports_replacement_realization ||
           capability == TPolicyRealizerCapability::supports_runtime_capable_realization;
}

} // namespace assembler::ecosystem_governance::policy_type_system

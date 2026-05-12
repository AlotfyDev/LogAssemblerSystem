#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerCapability.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerStatus.hpp"

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
 *   TPolicyRealizerView is a read-only summary of a realizer interface
 *   participant: id, status, capabilities, and descriptive name. It exposes
 *   no target instance and performs no runtime action.
 */
struct TPolicyRealizerView final
{
    TPolicyRealizerId realizer_id{};
    TPolicyRealizerStatus status{TPolicyRealizerStatus::unknown};
    std::string name{};
    std::vector<TPolicyRealizerCapability> capabilities{};

    [[nodiscard]] bool IsReady() const noexcept { return policy_type_system::IsReady(status); }
    [[nodiscard]] bool HasCapability(TPolicyRealizerCapability capability) const noexcept
    {
        return std::find(capabilities.begin(), capabilities.end(), capability) != capabilities.end();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

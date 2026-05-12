#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContextId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationContext.hpp
 * Wave: EG-POL-W18_Realization_Contract_Foundation
 * Domain: ecosystem_governance / policy_type_system / realization_contract
 *
 * Architectural boundary:
 *   W18 opens Phase C — Policy Runtime Readiness. It implements the first
 *   realization-contract foundation derived from EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness
 *   and validated by EG-POL-ARCH-008_Compliance_And_Validation_Matrix. The
 *   wave is descriptive and non-executing: it defines contract identity,
 *   contract kind, realization context identity, preconditions, failure
 *   descriptors, trace descriptors, contract carriers, contract views, context
 *   carriers, and realization requests without implementing TPolicyRealizer,
 *   target invocation, runtime mutation, scheduling, or policy execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity, policy family, policy version, scope,
 *     status, issue, and result vocabulary.
 *   - W05 supplies observation/audit and trace vocabulary; W18 may reference
 *     trace concepts but does not export telemetry or persist audit data.
 *   - W06 supplies realization binding and target-kind descriptors while
 *     preserving descriptor-only boundaries. W18 consumes those descriptors
 *     and formalizes realization contracts without becoming a realizer.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics; W18 requires assignment
 *     references but does not activate or execute assignments.
 *   - W12 and W13 supply family/scope and target-capability foundations.
 *   - W14 supplies compatibility reports that are preconditions for W18.
 *   - W15 supplies assignment lifecycle states that gate realization readiness.
 *   - W16 and W17 supply source/publication and registry-versioning views
 *     consumed by readiness workflows.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-007 states that assigned, active, runtime-ready, realized, and
 *   executed are separate states; realization contract is not realizer; runtime
 *   readiness is not runtime execution; target capability is not a method call;
 *   registry entry is not a runtime handle; trace is not authority. This file
 *   preserves those non-collapse rules.
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
 *
 * File responsibility:
 *   TPolicyRealizationContext bundles policy, assignment, target, capability, compatibility, registry, authority, trace, and environment metadata needed for readiness evaluation. It references descriptors only and does not own target runtime state.
 */

struct TPolicyRealizationContext final
{
    TPolicyRealizationContextId context_id{};
    TPolicyId policy_id{};
    TPolicyVersion policy_version{};
    std::uint64_t assignment_id{0};
    TPolicyAssignmentLifecycleState assignment_state{TPolicyAssignmentLifecycleState::unknown};
    std::uint64_t target_reference_id{0};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    TPolicyTargetCapabilitySet target_capabilities{};
    TPolicyFamilyCompatibilityReport compatibility_report{};
    TPolicyRealizationContractId contract_id{};
    std::uint64_t registry_entry_id{0};
    std::uint64_t publication_record_id{0};
    std::uint64_t authority_decision_id{0};
    std::uint64_t trace_id{0};
    bool target_is_quarantined{false};
    bool runtime_environment_available{false};
    std::string note{};

    [[nodiscard]] bool HasPolicy() const noexcept { return policy_id.IsValid() && !policy_version.IsZero(); }
    [[nodiscard]] bool HasAssignment() const noexcept { return assignment_id != 0 && assignment_state != TPolicyAssignmentLifecycleState::unknown; }
    [[nodiscard]] bool HasTargetDescriptor() const noexcept { return target_reference_id != 0 && target_kind != TPolicyTargetKind::unknown; }
    [[nodiscard]] bool HasContract() const noexcept { return contract_id.IsValid(); }
    [[nodiscard]] bool HasTrace() const noexcept { return trace_id != 0; }

    [[nodiscard]] bool IsStructurallyUsable() const noexcept
    {
        return context_id.IsValid() && HasPolicy() && HasAssignment() && HasTargetDescriptor() && HasContract();
    }

    [[nodiscard]] bool MayEvaluateReadiness() const noexcept
    {
        return IsStructurallyUsable() &&
               MayPlanRealization(assignment_state) &&
               !target_is_quarantined;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

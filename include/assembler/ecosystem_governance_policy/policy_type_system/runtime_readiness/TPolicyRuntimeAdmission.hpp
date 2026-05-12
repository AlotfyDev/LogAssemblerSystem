#pragma once

#include <cstdint>
#include <string>
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationRequest.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeAdmission.hpp

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
 *   TPolicyRuntimeAdmission describes whether a policy-assignment-context may
 *   be admitted into runtime readiness evaluation. It gathers the minimum
 *   non-executing governance indicators: assignment state, compatibility,
 *   contract presence, authority/publication flags, conflict state, quarantine,
 *   and trace availability. Admission does not mean execution; it only allows
 *   readiness evaluation to proceed.
 */

struct TPolicyRuntimeAdmission final
{
    TPolicyAssignmentLifecycleState assignment_state{TPolicyAssignmentLifecycleState::unknown};
    TPolicyFamilyCompatibilityReport compatibility_report{};
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationRequest request{};
    bool publication_satisfied{false};
    bool authority_satisfied{false};
    bool conflict_clear{true};
    bool not_quarantined{true};
    bool trace_available{false};
    std::string note{};

    [[nodiscard]] bool HasActiveOrEligibleAssignment() const noexcept
    {
        return assignment_state == TPolicyAssignmentLifecycleState::active ||
               assignment_state == TPolicyAssignmentLifecycleState::pending_replacement;
    }

    [[nodiscard]] bool HasContract() const noexcept { return contract_id.IsValid(); }
    [[nodiscard]] bool HasPositiveCompatibility() const noexcept { return compatibility_report.IsPositive() && !compatibility_report.IsBlocking(); }

    [[nodiscard]] bool CanEnterReadinessEvaluation() const noexcept
    {
        return HasActiveOrEligibleAssignment() &&
               HasPositiveCompatibility() &&
               HasContract() &&
               publication_satisfied &&
               authority_satisfied &&
               conflict_clear &&
               not_quarantined &&
               trace_available;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system

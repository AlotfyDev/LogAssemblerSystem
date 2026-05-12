#pragma once

#include <string>
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeAdmission.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessGate.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContract.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeReadinessEvaluator.hpp

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
 *   TPolicyRuntimeReadinessEvaluator performs a conservative, non-executing
 *   readiness evaluation over admission data and a realization contract. It
 *   produces a TPolicyRuntimeReadinessReport. It does not invoke the target,
 *   does not activate an assignment, does not realize a policy, and does not
 *   mutate runtime state.
 */

class TPolicyRuntimeReadinessEvaluator final
{
public:
    [[nodiscard]] TPolicyRuntimeReadinessReport Evaluate(
        const TPolicyRuntimeAdmission& admission,
        const TPolicyRealizationContract& contract) const
    {
        TPolicyRuntimeReadinessReport report;
        report.contract_id = contract.contract_id;

        auto gate = [](TPolicyRuntimeReadinessGateKind kind, bool ok, std::string note)
        {
            return TPolicyRuntimeReadinessGate{
                kind,
                ok ? TPolicyRuntimeReadinessGateStatus::passed : TPolicyRuntimeReadinessGateStatus::blocked,
                std::move(note)};
        };

        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::assignment, admission.HasActiveOrEligibleAssignment(), "assignment must be active or pending replacement"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::compatibility, admission.HasPositiveCompatibility(), "compatibility report must be positive and non-blocking"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::contract, admission.HasContract() && contract.IsValidContract(), "realization contract must exist and be valid"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::publication, admission.publication_satisfied || !contract.requires_publication, "publication must be satisfied when required"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::authority, admission.authority_satisfied || !contract.requires_authority, "authority must be satisfied when required"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::conflict, admission.conflict_clear, "blocking conflicts must be absent or resolved"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::quarantine, admission.not_quarantined, "policy, assignment, and target context must not be quarantined"));
        report.AddGate(gate(TPolicyRuntimeReadinessGateKind::trace, admission.trace_available || !contract.requires_trace, "trace must be available when required"));

        if (report.gate_set.HasBlockingGate())
        {
            report.state = TPolicyRuntimeReadinessState::blocked;
            report.AddIssue(TPolicyRuntimeReadinessIssue::Blocking(
                TPolicyRuntimeReadinessIssueKind::custom,
                "one or more mandatory runtime readiness gates failed"));
            report.recommendation = "do not proceed to realization planning";
            return report;
        }

        report.state = contract.RequiresRuntimeReadiness() ?
            TPolicyRuntimeReadinessState::runtime_ready :
            TPolicyRuntimeReadinessState::runtime_ready_with_warnings;
        report.recommendation = contract.RequiresRuntimeReadiness() ?
            "runtime readiness passed for runtime-capable contract" :
            "contract does not strictly require runtime readiness; readiness is reported as warning-level positive";
        return report;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system

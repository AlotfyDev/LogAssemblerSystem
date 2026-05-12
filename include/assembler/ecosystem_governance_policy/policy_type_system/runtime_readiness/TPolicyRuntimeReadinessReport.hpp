#pragma once

#include <cstdint>
#include <string>
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessGate.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationTrace.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeReadinessReport.hpp

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
 *   TPolicyRuntimeReadinessReport records the outcome of readiness evaluation.
 *   It aggregates gate results, issues, contract identity, trace evidence, and
 *   final readiness state. It is a reporting carrier, not an execution plan and
 *   not a realizer.
 */

struct TPolicyRuntimeReadinessReport final
{
    TPolicyRuntimeReadinessState state{TPolicyRuntimeReadinessState::not_evaluated};
    TPolicyRealizationContractId contract_id{};
    TPolicyRuntimeReadinessGateSet gate_set{};
    TPolicyRuntimeReadinessIssueSet issue_set{};
    TPolicyRealizationTrace trace{};
    std::string recommendation{};
    std::string note{};

    [[nodiscard]] bool IsPositive() const noexcept { return ::assembler::ecosystem_governance::policy_type_system::IsPositive(state); }
    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return ::assembler::ecosystem_governance::policy_type_system::IsBlocking(state) ||
               gate_set.HasBlockingGate() ||
               issue_set.HasBlockingIssue();
    }

    [[nodiscard]] bool MayProceedToRealizationPlanning() const noexcept
    {
        return ::assembler::ecosystem_governance::policy_type_system::MayProceedToRealizationPlanning(state) && !IsBlocking();
    }

    void AddGate(TPolicyRuntimeReadinessGate gate) { gate_set.Add(std::move(gate)); }
    void AddIssue(TPolicyRuntimeReadinessIssue issue)
    {
        if (issue.IsBlocking() && state == TPolicyRuntimeReadinessState::runtime_ready)
        {
            state = issue.IsForbidden() ? TPolicyRuntimeReadinessState::forbidden : TPolicyRuntimeReadinessState::blocked;
        }
        issue_set.Add(std::move(issue));
    }

    [[nodiscard]] static TPolicyRuntimeReadinessReport Ready(TPolicyRealizationContractId contract)
    {
        TPolicyRuntimeReadinessReport report;
        report.state = TPolicyRuntimeReadinessState::runtime_ready;
        report.contract_id = contract;
        report.recommendation = "runtime readiness passed; realization planning may be considered";
        return report;
    }

    [[nodiscard]] static TPolicyRuntimeReadinessReport Blocked(TPolicyRealizationContractId contract, std::string reason)
    {
        TPolicyRuntimeReadinessReport report;
        report.state = TPolicyRuntimeReadinessState::blocked;
        report.contract_id = contract;
        report.recommendation = "runtime readiness blocked";
        report.AddIssue(TPolicyRuntimeReadinessIssue::Blocking(TPolicyRuntimeReadinessIssueKind::custom, std::move(reason)));
        return report;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system

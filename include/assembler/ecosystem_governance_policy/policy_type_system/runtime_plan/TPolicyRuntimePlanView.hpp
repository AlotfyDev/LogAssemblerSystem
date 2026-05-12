#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlan.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimePlanView.hpp

 * Wave: EG-POL-W20_Policy_Runtime_Plan
 * Domain: ecosystem_governance / policy_type_system / runtime_plan
 *
 * Architectural boundary:
 *   W20 implements the Policy Runtime Plan model that follows W18 Realization
 *   Contract Foundation and W19 Runtime Readiness Model. It is derived from
 *   EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness and guarded by
 *   EG-POL-ARCH-008_Compliance_And_Validation_Matrix. A runtime plan is a
 *   pre-execution, non-mutating plan artifact: it may describe ordered steps
 *   a future realizer could consume, but it is not TPolicyRealizer, not
 *   TPolicyExecutor, not target invocation, not runtime mutation, not scheduler
 *   behavior, not material circulation, not communication binding, and not
 *   add-on execution.
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
 *   - W19 supplies runtime admission, readiness gates, readiness issues, readiness reports, and readiness evaluators.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W20 sits after runtime-ready and before any realizer interface. It can
 *   express a plan for later realization consideration, but that plan remains
 *   descriptive. Passing readiness and creating a plan does not execute policy
 *   behavior and does not prove target mutation, downstream success, or external
 *   side effects.
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
 *   TPolicyRuntimePlanView provides a read-only summary of a runtime plan. It
 *   supports diagnostics, reporting, and later compliance checks without
 *   exposing mutable plan internals and without executing the plan.
 */

struct TPolicyRuntimePlanView final
{
    TPolicyRuntimePlanId plan_id{};
    TPolicyRuntimePlanStatus status{TPolicyRuntimePlanStatus::unknown};
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationContextId context_id{};
    std::uint64_t authority_evidence_id{0};
    std::uint64_t trace_id{0};
    std::uint64_t step_count{0};
    std::uint64_t issue_count{0};
    bool structurally_valid{false};
    bool positive_readiness{false};
    bool plan_ready{false};
    std::string recommendation{};

    [[nodiscard]] bool IsPositive() const noexcept
    {
        return ::assembler::ecosystem_governance::policy_type_system::IsPositive(status) && plan_ready;
    }

    [[nodiscard]] static TPolicyRuntimePlanView FromPlan(const TPolicyRuntimePlan& plan)
    {
        TPolicyRuntimePlanView view;
        view.plan_id = plan.plan_id;
        view.status = plan.status;
        view.contract_id = plan.contract_id;
        view.context_id = plan.context_id;
        view.authority_evidence_id = plan.authority_evidence_id;
        view.trace_id = plan.trace.trace_ref.value;
        view.step_count = static_cast<std::uint64_t>(plan.step_set.Count());
        view.issue_count = static_cast<std::uint64_t>(plan.issue_set.Count());
        view.structurally_valid = plan.IsStructurallyValid();
        view.positive_readiness = plan.HasPositiveReadiness();
        view.plan_ready = plan.IsPlanReady();
        view.recommendation = plan.recommendation;
        return view;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

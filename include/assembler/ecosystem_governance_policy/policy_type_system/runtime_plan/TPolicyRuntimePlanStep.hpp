#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimePlanStep.hpp

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
 *   TPolicyRuntimePlanStep defines descriptive plan steps a future realizer
 *   may later consume. A step is not a function call and not target invocation.
 *   It records intended ordering, guard/readiness references, and semantic
 *   step kind without executing the behavior it describes.
 */

enum class TPolicyRuntimePlanStepKind : std::uint8_t
{
    unknown = 0,
    verify_contract = 1,
    verify_runtime_readiness = 2,
    verify_authority = 3,
    verify_trace = 4,
    prepare_realization_context = 5,
    prepare_target_capability_view = 6,
    prepare_replacement_guard = 7,
    prepare_observation_hook = 8,
    prepare_fallback_guard = 9,
    submit_to_future_realizer = 10,
    no_op = 11
};

struct TPolicyRuntimePlanStep final
{
    std::uint32_t sequence{0};
    TPolicyRuntimePlanStepKind kind{TPolicyRuntimePlanStepKind::unknown};
    bool required{true};
    bool satisfied{false};
    std::uint64_t reference_id{0};
    std::string label{};
    std::string note{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return sequence != 0 && kind != TPolicyRuntimePlanStepKind::unknown && !label.empty();
    }

    [[nodiscard]] bool IsReady() const noexcept
    {
        return IsValid() && (!required || satisfied);
    }
};

struct TPolicyRuntimePlanStepSet final
{
    std::vector<TPolicyRuntimePlanStep> steps{};

    void Add(TPolicyRuntimePlanStep step)
    {
        if (step.IsValid()) steps.push_back(std::move(step));
    }

    [[nodiscard]] std::size_t Count() const noexcept { return steps.size(); }
    [[nodiscard]] bool Empty() const noexcept { return steps.empty(); }
    [[nodiscard]] bool AllRequiredSatisfied() const noexcept
    {
        for (const auto& step : steps) if (step.required && !step.satisfied) return false;
        return true;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeReadinessGate.hpp

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
 *   TPolicyRuntimeReadinessGate defines the named readiness gates that must be
 *   checked before runtime realization can be considered. Gate evaluation is
 *   descriptive: it reports pass, warning, conditional, deferred, failed,
 *   blocked, or forbidden states without invoking any target capability.
 */

enum class TPolicyRuntimeReadinessGateKind : std::uint8_t
{
    unknown = 0,
    policy_validity = 1,
    policy_lifecycle = 2,
    publication = 3,
    assignment = 4,
    compatibility = 5,
    target_kind = 6,
    target_capability = 7,
    authority = 8,
    conflict = 9,
    replacement = 10,
    observation = 11,
    trace = 12,
    runtime_environment = 13,
    quarantine = 14,
    contract = 15
};

enum class TPolicyRuntimeReadinessGateStatus : std::uint8_t
{
    unknown = 0,
    passed = 1,
    passed_with_warning = 2,
    conditionally_passed = 3,
    not_applicable = 4,
    deferred = 5,
    failed = 6,
    blocked = 7,
    forbidden = 8
};

struct TPolicyRuntimeReadinessGate final
{
    TPolicyRuntimeReadinessGateKind kind{TPolicyRuntimeReadinessGateKind::unknown};
    TPolicyRuntimeReadinessGateStatus status{TPolicyRuntimeReadinessGateStatus::unknown};
    std::string note{};

    [[nodiscard]] bool IsKnown() const noexcept { return kind != TPolicyRuntimeReadinessGateKind::unknown; }
    [[nodiscard]] bool IsPositive() const noexcept
    {
        return status == TPolicyRuntimeReadinessGateStatus::passed ||
               status == TPolicyRuntimeReadinessGateStatus::passed_with_warning ||
               status == TPolicyRuntimeReadinessGateStatus::conditionally_passed ||
               status == TPolicyRuntimeReadinessGateStatus::not_applicable;
    }
    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return status == TPolicyRuntimeReadinessGateStatus::failed ||
               status == TPolicyRuntimeReadinessGateStatus::blocked ||
               status == TPolicyRuntimeReadinessGateStatus::forbidden;
    }
};

struct TPolicyRuntimeReadinessGateSet final
{
    std::vector<TPolicyRuntimeReadinessGate> gates{};

    void Add(TPolicyRuntimeReadinessGate gate) { if (gate.IsKnown()) gates.push_back(std::move(gate)); }
    [[nodiscard]] bool Empty() const noexcept { return gates.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return gates.size(); }
    [[nodiscard]] bool HasBlockingGate() const noexcept
    {
        for (const auto& gate : gates) { if (gate.IsBlocking()) return true; }
        return false;
    }
    [[nodiscard]] bool AllPositive() const noexcept
    {
        if (gates.empty()) return false;
        for (const auto& gate : gates) { if (!gate.IsPositive()) return false; }
        return true;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system

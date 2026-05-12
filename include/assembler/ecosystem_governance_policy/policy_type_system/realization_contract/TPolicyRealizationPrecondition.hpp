#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationPrecondition.hpp
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
 *   TPolicyRealizationPrecondition defines readiness and contract preconditions required before realization planning may be considered. It reports positive, deferred, missing, failed, or forbidden conditions without executing behavior.
 */

enum class TPolicyRealizationPreconditionKind : std::uint8_t
{
    unknown = 0,
    policy_valid = 1,
    policy_family_known = 2,
    policy_type_known = 3,
    publication_state_acceptable = 4,
    registry_entry_available = 5,
    assignment_active_or_contract_eligible = 6,
    compatibility_positive = 7,
    target_kind_known = 8,
    target_capabilities_satisfied = 9,
    authority_granted = 10,
    conflict_clear_or_resolved = 11,
    lifecycle_compatible = 12,
    replacement_safe_if_applicable = 13,
    observation_ready_if_required = 14,
    runtime_readiness_positive_if_required = 15,
    realization_contract_applicable = 16,
    trace_available = 17,
    not_quarantined = 18
};

enum class TPolicyRealizationPreconditionStatus : std::uint8_t
{
    unknown = 0,
    satisfied = 1,
    satisfied_with_warning = 2,
    conditionally_satisfied = 3,
    deferred = 4,
    missing = 5,
    failed = 6,
    forbidden = 7
};

struct TPolicyRealizationPrecondition final
{
    TPolicyRealizationPreconditionKind kind{TPolicyRealizationPreconditionKind::unknown};
    TPolicyRealizationPreconditionStatus status{TPolicyRealizationPreconditionStatus::unknown};
    std::string note{};

    [[nodiscard]] bool IsKnown() const noexcept { return kind != TPolicyRealizationPreconditionKind::unknown; }
    [[nodiscard]] bool IsPositive() const noexcept
    {
        return status == TPolicyRealizationPreconditionStatus::satisfied ||
               status == TPolicyRealizationPreconditionStatus::satisfied_with_warning ||
               status == TPolicyRealizationPreconditionStatus::conditionally_satisfied;
    }
    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return status == TPolicyRealizationPreconditionStatus::missing ||
               status == TPolicyRealizationPreconditionStatus::failed ||
               status == TPolicyRealizationPreconditionStatus::forbidden;
    }
};

struct TPolicyRealizationPreconditionSet final
{
    std::vector<TPolicyRealizationPrecondition> preconditions{};

    [[nodiscard]] bool Empty() const noexcept { return preconditions.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return preconditions.size(); }
    void Add(TPolicyRealizationPrecondition precondition) { if (precondition.IsKnown()) preconditions.push_back(std::move(precondition)); }

    [[nodiscard]] bool AllPositive() const noexcept
    {
        if (preconditions.empty()) return false;
        for (const auto& precondition : preconditions)
        {
            if (!precondition.IsPositive()) return false;
        }
        return true;
    }

    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        for (const auto& precondition : preconditions)
        {
            if (precondition.IsBlocking()) return true;
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

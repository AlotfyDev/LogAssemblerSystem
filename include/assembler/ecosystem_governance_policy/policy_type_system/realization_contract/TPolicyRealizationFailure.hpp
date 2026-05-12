#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationFailure.hpp
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
 *   TPolicyRealizationFailure classifies failures in readiness evaluation, realization planning, or future realization attempts. It records failure meaning and severity without repairing, rolling back, or mutating runtime state.
 */

enum class TPolicyRealizationFailureKind : std::uint8_t
{
    unknown = 0,
    policy_invalid = 1,
    assignment_not_active = 2,
    compatibility_failed = 3,
    target_kind_unknown = 4,
    missing_capability = 5,
    authority_missing_or_rejected = 6,
    conflict_blocking = 7,
    replacement_unsafe = 8,
    publication_invalid = 9,
    contract_missing = 10,
    contract_mismatch = 11,
    runtime_environment_not_ready = 12,
    observation_missing = 13,
    quarantined = 14,
    forbidden_realization = 15,
    target_invocation_forbidden = 16
};

enum class TPolicyRealizationFailureSeverity : std::uint8_t
{
    unknown = 0,
    info = 1,
    warning = 2,
    blocking = 3,
    critical = 4,
    forbidden = 5
};

struct TPolicyRealizationFailure final
{
    TPolicyRealizationFailureKind kind{TPolicyRealizationFailureKind::unknown};
    TPolicyRealizationFailureSeverity severity{TPolicyRealizationFailureSeverity::unknown};
    std::string message{};

    [[nodiscard]] bool IsKnown() const noexcept { return kind != TPolicyRealizationFailureKind::unknown; }
    [[nodiscard]] bool BlocksReadiness() const noexcept
    {
        return severity == TPolicyRealizationFailureSeverity::blocking ||
               severity == TPolicyRealizationFailureSeverity::critical ||
               severity == TPolicyRealizationFailureSeverity::forbidden;
    }
    [[nodiscard]] bool IsForbidden() const noexcept { return severity == TPolicyRealizationFailureSeverity::forbidden; }
};

struct TPolicyRealizationFailureSet final
{
    std::vector<TPolicyRealizationFailure> failures{};

    void Add(TPolicyRealizationFailure failure) { if (failure.IsKnown()) failures.push_back(std::move(failure)); }
    [[nodiscard]] bool Empty() const noexcept { return failures.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return failures.size(); }
    [[nodiscard]] bool HasBlockingFailure() const noexcept
    {
        for (const auto& failure : failures)
        {
            if (failure.BlocksReadiness()) return true;
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

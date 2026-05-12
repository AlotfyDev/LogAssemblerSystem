#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContext.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContextId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationRequest.hpp
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
 *   TPolicyRealizationRequest represents a governed ask to evaluate readiness, create a realization plan, or later request controlled realization. A request is not execution and must not directly invoke target behavior.
 */

enum class TPolicyRealizationRequestKind : std::uint8_t
{
    unknown = 0,
    readiness_evaluation = 1,
    realization_plan = 2,
    manual_realization = 3,
    configuration_realization = 4,
    lifecycle_realization = 5,
    replacement_realization = 6,
    runtime_realization = 7,
    dry_run_realization = 8,
    rollback_realization = 9,
    cancel_realization = 10
};

struct TPolicyRealizationRequest final
{
    std::uint64_t request_id{0};
    TPolicyRealizationRequestKind request_kind{TPolicyRealizationRequestKind::unknown};
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationContextId context_id{};
    TPolicyRealizationMode requested_mode{TPolicyRealizationMode::unknown};
    std::uint64_t authority_evidence_id{0};
    std::uint64_t readiness_report_id{0};
    std::uint64_t trace_id{0};
    bool dry_run{false};
    std::string request_note{};

    [[nodiscard]] bool IsValidRequest() const noexcept
    {
        return request_id != 0 &&
               request_kind != TPolicyRealizationRequestKind::unknown &&
               contract_id.IsValid() &&
               context_id.IsValid() &&
               requested_mode != TPolicyRealizationMode::unknown;
    }

    [[nodiscard]] bool HasAuthorityEvidence() const noexcept { return authority_evidence_id != 0; }
    [[nodiscard]] bool HasTrace() const noexcept { return trace_id != 0; }
    [[nodiscard]] bool IsRuntimeRequest() const noexcept { return request_kind == TPolicyRealizationRequestKind::runtime_realization; }
    [[nodiscard]] bool IsPlanningOnly() const noexcept
    {
        return request_kind == TPolicyRealizationRequestKind::readiness_evaluation ||
               request_kind == TPolicyRealizationRequestKind::realization_plan ||
               dry_run;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationPrecondition.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationContract.hpp
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
 *   TPolicyRealizationContract describes the governed contract under which an active assignment may later be prepared for realization. It records required family, target, capabilities, preconditions, authority, publication, trace, and mode expectations without becoming a realizer.
 */

struct TPolicyRealizationContract final
{
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationContractKind contract_kind{TPolicyRealizationContractKind::unknown};
    TPolicyFamilyKind policy_family_kind{TPolicyFamilyKind::unspecified};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    TPolicyRealizationMode expected_realization_mode{TPolicyRealizationMode::unknown};
    std::vector<TPolicyTargetCapabilityKind> required_capabilities{};
    TPolicyRealizationPreconditionSet required_preconditions{};
    bool requires_active_assignment{true};
    bool requires_positive_compatibility{true};
    bool requires_authority{true};
    bool requires_publication{true};
    bool requires_trace{true};
    std::string contract_name{};
    std::string notes{};

    [[nodiscard]] bool IsValidContract() const noexcept
    {
        return contract_id.IsValid() &&
               contract_kind != TPolicyRealizationContractKind::unknown &&
               !IsForbidden(contract_kind) &&
               policy_family_kind != TPolicyFamilyKind::unspecified &&
               target_kind != TPolicyTargetKind::unknown &&
               expected_realization_mode != TPolicyRealizationMode::unknown;
    }

    [[nodiscard]] bool RequiresRuntimeReadiness() const noexcept
    {
        return contract_kind == TPolicyRealizationContractKind::runtime_capable_realization ||
               contract_kind == TPolicyRealizationContractKind::configuration_realization ||
               contract_kind == TPolicyRealizationContractKind::lifecycle_realization ||
               contract_kind == TPolicyRealizationContractKind::replacement_realization;
    }

    [[nodiscard]] bool HasCapabilityRequirements() const noexcept
    {
        return !required_capabilities.empty();
    }

    [[nodiscard]] bool HasMinimumGovernanceRequirements() const noexcept
    {
        return requires_positive_compatibility && requires_authority && requires_trace;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

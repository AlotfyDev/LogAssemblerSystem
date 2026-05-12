#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyCompatibilityRule.hpp

 * Wave: EG-POL-W14_Family_Target_Compatibility_Matrix
 * Domain: ecosystem_governance / policy_type_system / compatibility_matrix
 *
 * Architectural boundary:
 *   W14 implements the first policy-family-to-target-kind compatibility matrix
 *   layer derived from EG-POL-ARCH-003_Policy_Family_Compatibility_Matrix. It
 *   follows W12 Policy Family And Scope and W13 Target Capability Contracts.
 *   The wave remains descriptive and non-executing: it defines compatibility
 *   rules, reports, and evaluation helpers without activating assignments,
 *   invoking targets, realizing policies, or mutating runtime components.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive identity and policy scope vocabulary.
 *   - W06 supplies target-kind descriptors and preserves the descriptor-only
 *     boundary for realization binding.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics; W14 does not activate
 *     assignments.
 *   - W11 supplies registry basics; W14 does not become a registry or service
 *     locator.
 *   - W12 supplies family and scope profiles consumed by compatibility rules.
 *   - W13 supplies target capability descriptors and capability sets consumed
 *     by compatibility rules.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-003 states that compatibility is distinct from assignment, that
 *   assignment is distinct from realization, that target capability is not a
 *   method call, and that the matrix must not become a runtime engine. This
 *   wave implements that matrix vocabulary at code level while preserving those
 *   boundaries.
 *
 * Explicit non-responsibilities:
 *   This file does not implement assignment lifecycle activation, authority
 *   roles, source publication, registry persistence, realization contracts,
 *   runtime readiness, TPolicyRealizer, TPolicyExecutor, target invocation,
 *   material circulation behavior, communication binding, add-on execution,
 *   telemetry, logging, or persistence.
 *
 * Current implementation posture:
 *   The current code is a conservative C++17 header-only foundation. The
 *   opening documentation describes the complete architectural responsibility,
 *   while the code intentionally remains a small set of value carriers and
 *   structural helpers.
 * File responsibility:
 *   TPolicyFamilyCompatibilityRule is one matrix row describing which policy
 *   family kind may target which target kind, which scopes are allowed, and
 *   which capabilities are required. It is an architectural rule carrier only;
 *   it does not evaluate concrete runtime state or invoke target behavior.
 */
struct TPolicyFamilyCompatibilityRule final
{
    std::string rule_id{};
    TPolicyFamilyKind policy_family_kind{TPolicyFamilyKind::unspecified};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    std::vector<TPolicyScope> allowed_scopes{};
    std::vector<TPolicyTargetCapabilityKind> required_capabilities{};
    std::vector<TPolicyTargetCapabilityKind> recommended_capabilities{};
    std::vector<TPolicyTargetCapabilityKind> forbidden_capabilities{};
    TPolicyRealizationMode realization_mode{TPolicyRealizationMode::unknown};
    bool lifecycle_required{true};
    bool replacement_required{false};
    bool observation_required{true};
    bool authority_required{false};
    bool registry_required{false};
    bool experimental{false};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return !rule_id.empty() &&
               IsKnownPolicyFamilyKind(policy_family_kind) &&
               IsKnown(target_kind);
    }

    [[nodiscard]] bool Matches(TPolicyFamilyKind family, TPolicyTargetKind target) const noexcept
    {
        return policy_family_kind == family && target_kind == target;
    }

    [[nodiscard]] bool AllowsScope(TPolicyScope scope) const noexcept
    {
        if (allowed_scopes.empty()) return true;
        for (auto allowed : allowed_scopes)
        {
            if (allowed == scope) return true;
        }
        return false;
    }

    [[nodiscard]] bool RequiresRuntimeRealization() const noexcept
    {
        return realization_mode == TPolicyRealizationMode::delegated_executor_path;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

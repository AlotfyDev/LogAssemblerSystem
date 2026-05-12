#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityMatrix.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyFamilyProfile family;
    family.kind = TPolicyFamilyKind::dispatch;
    family.family_id = TPolicyFamilyId{1};
    family.canonical_name = "dispatcher_policy_family";
    family.default_scope = TPolicyScope::domain;
    family.AddAllowedScope(TPolicyScope::domain);
    assert(family.IsValid());

    TPolicyTargetCapabilityDescriptor assignment_capability;
    assignment_capability.target_kind = TPolicyTargetKind::dispatcher;
    assignment_capability.kind = TPolicyTargetCapabilityKind::accepts_policy_assignment;
    assignment_capability.capability_id = TPolicyTargetCapabilityId{1};
    assignment_capability.strength = TPolicyTargetCapabilityStrength::required;
    assignment_capability.mutability = TPolicyTargetCapabilityMutability::read_only;
    assignment_capability.canonical_name = "accepts_policy_assignment";

    TPolicyTargetCapabilityDescriptor readiness_capability;
    readiness_capability.target_kind = TPolicyTargetKind::dispatcher;
    readiness_capability.kind = TPolicyTargetCapabilityKind::supports_readiness_check;
    readiness_capability.capability_id = TPolicyTargetCapabilityId{2};
    readiness_capability.strength = TPolicyTargetCapabilityStrength::required;
    readiness_capability.mutability = TPolicyTargetCapabilityMutability::read_only;
    readiness_capability.canonical_name = "supports_readiness_check";

    TPolicyTargetCapabilitySet capabilities;
    capabilities.Add(assignment_capability);
    capabilities.Add(readiness_capability);

    TPolicyFamilyCompatibilityRule rule;
    rule.rule_id = "dispatch-to-dispatcher";
    rule.policy_family_kind = TPolicyFamilyKind::dispatch;
    rule.target_kind = TPolicyTargetKind::dispatcher;
    rule.allowed_scopes.push_back(TPolicyScope::domain);
    rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::accepts_policy_assignment);
    rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_readiness_check);
    rule.authority_required = true;

    TPolicyFamilyCompatibilityMatrix matrix;
    matrix.AddRule(rule);
    assert(matrix.HasRule(TPolicyFamilyKind::dispatch, TPolicyTargetKind::dispatcher));

    TPolicyScopePath target_scope;
    target_scope.scope = TPolicyScope::domain;
    target_scope.segments = {"system", "material_circulation", "dispatcher"};

    auto report = matrix.Evaluate(family, TPolicyTargetKind::dispatcher, target_scope, capabilities);
    assert(report.IsPositive());
    assert(!report.HasMissingCapabilities());
    assert(report.satisfied_capabilities.size() == 2);
    return report.IsBlocking() ? 1 : 0;
}

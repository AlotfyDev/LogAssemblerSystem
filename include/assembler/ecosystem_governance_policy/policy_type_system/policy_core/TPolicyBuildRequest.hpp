#pragma once

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicySource.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyProvenance.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyBuildRequest.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicyBuildRequest is the W09 aggregate-construction input descriptor for
 *   the minimum identity side of a TPolicy. It represents a request to create or
 *   seed an aggregate policy object without also smuggling in assignment,
 *   registry lookup, realization execution, graph traversal, communication
 *   binding, or target ownership.
 *
 * Why this file exists in W09:
 *   TPolicy needs a small, explicit construction input so smoke tests and future
 *   factory layers can create aggregates from identity data in a reviewable way.
 *   Keeping this file separate from TPolicy prevents constructor arguments from
 *   becoming an implicit, undocumented policy-building protocol.
 *
 * Relationship to previous waves:
 *   This file uses W01 identity primitives only. Lower-layer structures from W02
 *   through W08 are attached to TPolicy after construction through explicit
 *   aggregate functions or future builder/factory layers.
 *
 * Relationship to other files in this wave:
 *   - TPolicy may be seeded from this request.
 *   - TPolicyBuildResult reports whether the request produced a structurally
 *     acceptable starting aggregate.
 *   - TPolicyValidationReport may explain why the request is incomplete.
 *
 * Relationship to future waves:
 *   Future factories may extend this request or introduce richer build plans for
 *   complete policies, but they must remain separate from assignment and
 *   registry workflows.
 *
 * Explicit non-responsibilities:
 *   TPolicyBuildRequest is not a builder, not a registry command, not an
 *   assignment request, not a policy graph construction language, not a
 *   traversal plan, not a realizer request, and not a target invocation packet.
 *
 * Current implementation note:
 *   W09 keeps this request identity-focused. Later waves may define a richer
 *   build plan once assignment and registry boundaries are clear.
 */
struct TPolicyBuildRequest final
{
    TPolicyId policy_id{};
    TPolicyFamilyId family_id{};
    TPolicyVersion version{};
    TPolicyScope scope{TPolicyScope::unspecified};
    TPolicySource source{};
    TPolicyProvenance provenance{};

    constexpr TPolicyBuildRequest() noexcept = default;

    constexpr TPolicyBuildRequest(
        TPolicyId policy,
        TPolicyFamilyId family,
        TPolicyVersion policy_version,
        TPolicyScope policy_scope) noexcept
        : policy_id(policy), family_id(family), version(policy_version), scope(policy_scope)
    {
    }

    [[nodiscard]] constexpr bool HasMinimumIdentity() const noexcept
    {
        return policy_id.IsValid() && family_id.IsValid() && !version.IsZero() && IsSpecified(scope);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

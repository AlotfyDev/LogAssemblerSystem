#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicyBundleDtoId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticPayloadRef.hpp"

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines the governance-produced DTO that carries policy semantic material toward a target domain. It is the semantic half of ARCH-009: identity, family, version, scope, clauses, lifecycle, replacement, observation, and realization-binding references are transported without target completion.
 *
 * Relationship to prior waves and ARCH-009:
 *   W01-W09 define the policy object foundation, W16-W17 define source/publication and registry versioning, and ARCH-009 clarifies that governance semantics are delivered before target-side realization definitions complete the policy object.
 *
 * Full intended picture:
 *   Future domain objects may accept this DTO through a domain intake boundary, validate it against target capabilities, and produce a completed policy object for host assignment. The DTO remains non-owning and descriptor-like.
 *
 * Explicit non-responsibilities:
 *   This file does not define target capability declarations, completed policy object creation, host assignment, safe-point switching, or realizer execution.
 */
struct TPolicyGovernanceSemanticBundleDto
{
    TPolicyBundleDtoId id;
    std::string policy_id_ref;
    std::string family_ref;
    std::string version_ref;
    std::string scope_ref;
    std::string publication_snapshot_ref;
    std::vector<TPolicySemanticPayloadRef> semantic_parts;
    std::vector<std::string> tags;

    [[nodiscard]] bool has_identity() const noexcept
    {
        return !id.empty() && !policy_id_ref.empty() && !family_ref.empty() && !version_ref.empty() && !scope_ref.empty();
    }

    [[nodiscard]] std::size_t semantic_part_count() const noexcept { return semantic_parts.size(); }

    void add_semantic_part(TPolicySemanticPayloadRef part)
    {
        semantic_parts.push_back(std::move(part));
    }

    [[nodiscard]] bool has_semantic_part(const std::string& name) const
    {
        for (const auto& part : semantic_parts)
        {
            if (part.name == name && !part.ref.empty()) return true;
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery

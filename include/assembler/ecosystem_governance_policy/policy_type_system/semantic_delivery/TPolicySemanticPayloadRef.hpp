#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines a lightweight reference to one semantic part inside a governance policy bundle, such as identity, clauses, lifecycle, replacement, observation, or realization-binding semantics.
 *
 * Relationship to prior waves and ARCH-009:
 *   W01-W09 define policy object foundation parts. ARCH-009 clarifies that governance sends a semantic half that must be completed by target capabilities and realization definitions. This reference points to those semantic parts without embedding their concrete representation.
 *
 * Full intended picture:
 *   Future source adapters may replace this string-based reference with typed handles or serialized payload descriptors. The boundary remains reference-oriented so it does not force source parsing or storage choices into core policy architecture.
 *
 * Explicit non-responsibilities:
 *   This file does not parse payloads, validate clause expressions, persist semantic payloads, or complete a policy object.
 */
struct TPolicySemanticPayloadRef
{
    std::string name;
    std::string ref;

    TPolicySemanticPayloadRef() = default;
    TPolicySemanticPayloadRef(std::string n, std::string r) : name(std::move(n)), ref(std::move(r)) {}
    [[nodiscard]] bool empty() const noexcept { return name.empty() || ref.empty(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery

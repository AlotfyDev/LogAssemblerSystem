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
 *   This header defines the stable identity of a policy semantic bundle DTO. The id names a governance-produced transfer artifact that carries policy semantics toward a target domain without implying assignment, completion, realization, or execution.
 *
 * Relationship to prior waves and ARCH-009:
 *   W01 introduced primitive policy identity, W16 introduced source/publication concepts, and W17 introduced registry publication views. ARCH-009 clarifies that governance semantics are delivered before target completion and assignment. This id names that semantic-delivery artifact only.
 *
 * Full intended picture:
 *   Future domain flows may correlate this id with policy ids, publication snapshots, assignment requests, target capability declarations, and completed-policy-object records. It remains a small value object so it can cross catalog, validation, and DTO boundaries safely.
 *
 * Explicit non-responsibilities:
 *   This file does not define policy object completion, target capability mapping, host assignment, safe-point switching, runtime realization, target invocation, persistence, or audit export.
 */
struct TPolicyBundleDtoId
{
    std::string value;

    TPolicyBundleDtoId() = default;
    explicit TPolicyBundleDtoId(std::string v) : value(std::move(v)) {}
    [[nodiscard]] bool empty() const noexcept { return value.empty(); }
};

inline bool operator==(const TPolicyBundleDtoId& a, const TPolicyBundleDtoId& b) noexcept { return a.value == b.value; }
inline bool operator!=(const TPolicyBundleDtoId& a, const TPolicyBundleDtoId& b) noexcept { return !(a == b); }

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery

#pragma once

#include <array>
#include <cstddef>
#include "TPolicyClause.hpp"
#include "TPolicyClauseView.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseSet.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseSet is a small bounded collection of policy-local clauses.
 *   The Policy Object graph requires one or more Clause Nodes or clause-bearing
 *   structures. This file provides an early non-allocating collection surface so
 *   the clause layer can be smoke-tested and later graph/aggregate layers can
 *   compose clause sets without pulling in dynamic storage policy.
 *
 * Why this file exists in W02:
 *   Clause presence is mandatory, but TPolicy aggregate and PolicyGraph are not
 *   allowed yet. TPolicyClauseSet gives W02 a way to express the required
 *   "one or more clauses" idea while preserving dependency order and avoiding
 *   premature graph or aggregate construction.
 *
 * Relationship to other files in this wave:
 *   - Stores TPolicyClause values.
 *   - Returns TPolicyClauseView for read-only access.
 *   - Uses TPolicyClauseStatus indirectly through member clauses.
 *
 * Relationship to future waves:
 *   - W03 replacement may map safe-point participation to clauses in a set.
 *   - W07 graph structure may derive clause nodes from this set or a richer
 *     graph-backed representation.
 *   - W09 TPolicy may compose a clause set or replace it with a richer internal
 *     representation while preserving the semantic role.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseSet is not a policy graph, not a traversal channel, not a
 *   scheduler, not an evaluator, and not a registry collection. It only stores
 *   primitive clause carriers under a fixed capacity.
 *
 * Current implementation note:
 *   W02 uses a fixed-size template to avoid allocator and ownership decisions.
 *   A later implementation may introduce different storage policies under the
 *   same semantic contract.
 */
template <std::size_t Capacity>
class TPolicyClauseSet final
{
public:
    using size_type = std::size_t;

    constexpr TPolicyClauseSet() noexcept = default;

    [[nodiscard]] constexpr size_type CapacityValue() const noexcept { return Capacity; }
    [[nodiscard]] constexpr size_type Size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool Empty() const noexcept { return size_ == 0; }
    [[nodiscard]] constexpr bool Full() const noexcept { return size_ >= Capacity; }

    [[nodiscard]] constexpr bool Add(const TPolicyClause& clause) noexcept
    {
        if (Full())
        {
            return false;
        }
        clauses_[size_] = clause;
        ++size_;
        return true;
    }

    [[nodiscard]] constexpr TPolicyClauseView At(size_type index) const noexcept
    {
        return index < size_ ? TPolicyClauseView{&clauses_[index]} : TPolicyClauseView{};
    }

    [[nodiscard]] constexpr bool Contains(TPolicyClauseId id) const noexcept
    {
        for (size_type i = 0; i < size_; ++i)
        {
            if (clauses_[i].id == id)
            {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool HasUsableClause() const noexcept
    {
        for (size_type i = 0; i < size_; ++i)
        {
            if (clauses_[i].IsStructurallyUsable())
            {
                return true;
            }
        }
        return false;
    }

private:
    std::array<TPolicyClause, Capacity> clauses_{};
    size_type size_{0};
};

} // namespace assembler::ecosystem_governance::policy_type_system

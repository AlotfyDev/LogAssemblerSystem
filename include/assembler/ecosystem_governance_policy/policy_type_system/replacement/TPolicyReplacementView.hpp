#pragma once

#include "TPolicyReplacementBoundary.hpp"
#include "TPolicyReplacementPlan.hpp"
#include "TPolicySafePoint.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyReplacementView.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicyReplacementView is a lightweight read-only projection over the W03
 *   replacement structures. It allows smoke tests, future diagnostics, future
 *   TPolicy views, and future observation records to inspect replacement
 *   readiness without mutating the underlying safe point, boundary, or plan.
 *
 * Why this file exists in W03:
 *   Every wave should provide a small view surface where useful. Replacement is
 *   especially prone to category collapse into execution. A read-only view helps
 *   separate inspection from action and keeps W03 descriptive.
 *
 * Relationship to other files in this wave:
 *   - It may view TPolicySafePoint, TPolicyReplacementBoundary, or
 *     TPolicyReplacementPlan.
 *   - It reuses IsStructurallyUsable and IsEligible functions exposed by those
 *     carriers.
 *
 * Relationship to future waves:
 *   - W05 observation may embed this view data in audit records.
 *   - W07 graph views may reference replacement views when reporting safe point
 *     node completeness.
 *   - W09 TPolicyView may expose replacement information through this view or a
 *     richer successor.
 *
 * Explicit non-responsibilities:
 *   TPolicyReplacementView does not change eligibility, approve a plan, execute
 *   replacement, call a realizer, own a target object, or persist audit records.
 *
 * Current implementation note:
 *   W03 represents a simple tagged view over pointers. Later waves may replace
 *   this with safer handles, variants, or span-like views once ownership rules
 *   are richer.
 */
struct TPolicyReplacementView final
{
    enum class SubjectKind : unsigned char
    {
        none = 0,
        safe_point = 1,
        boundary = 2,
        plan = 3
    };

    SubjectKind subject_kind{SubjectKind::none};
    const TPolicySafePoint* safe_point{nullptr};
    const TPolicyReplacementBoundary* boundary{nullptr};
    const TPolicyReplacementPlan* plan{nullptr};

    [[nodiscard]] static constexpr TPolicyReplacementView FromSafePoint(const TPolicySafePoint& value) noexcept
    {
        TPolicyReplacementView view{};
        view.subject_kind = SubjectKind::safe_point;
        view.safe_point = &value;
        return view;
    }

    [[nodiscard]] static constexpr TPolicyReplacementView FromBoundary(const TPolicyReplacementBoundary& value) noexcept
    {
        TPolicyReplacementView view{};
        view.subject_kind = SubjectKind::boundary;
        view.boundary = &value;
        return view;
    }

    [[nodiscard]] static constexpr TPolicyReplacementView FromPlan(const TPolicyReplacementPlan& value) noexcept
    {
        TPolicyReplacementView view{};
        view.subject_kind = SubjectKind::plan;
        view.plan = &value;
        return view;
    }

    [[nodiscard]] constexpr bool HasSubject() const noexcept { return subject_kind != SubjectKind::none; }
    [[nodiscard]] constexpr bool IsSafePointView() const noexcept { return subject_kind == SubjectKind::safe_point && safe_point != nullptr; }
    [[nodiscard]] constexpr bool IsBoundaryView() const noexcept { return subject_kind == SubjectKind::boundary && boundary != nullptr; }
    [[nodiscard]] constexpr bool IsPlanView() const noexcept { return subject_kind == SubjectKind::plan && plan != nullptr; }

    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return (IsSafePointView() && safe_point->IsStructurallyUsable()) ||
               (IsBoundaryView() && boundary->IsStructurallyUsable()) ||
               (IsPlanView() && plan->IsStructurallyUsable());
    }

    [[nodiscard]] constexpr bool IsEligible() const noexcept
    {
        return (IsSafePointView() && safe_point->IsEligible()) ||
               (IsBoundaryView() && boundary->IsEligible()) ||
               (IsPlanView() && plan->IsEligible());
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

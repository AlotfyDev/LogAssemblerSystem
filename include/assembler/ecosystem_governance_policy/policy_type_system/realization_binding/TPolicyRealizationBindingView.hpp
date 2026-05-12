#pragma once

#include "TPolicyRealizationBinding.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationBindingView.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationBindingView is the safe read-only observation surface for
 *   a realization binding. It lets later policy graph, TPolicy aggregate,
 *   assignment, and diagnostics layers inspect binding identity, mechanism mode,
 *   target kind, lifecycle state, replacement eligibility, and trace presence
 *   without mutating the binding or invoking any mechanism.
 *
 * Why this file exists in W06:
 *   Each policy foundation wave exposes view objects where useful so later waves
 *   can depend on stable read-only surfaces instead of reaching into mutable or
 *   internal structures. W06 needs such a view because realization binding is
 *   architecturally sensitive and must not become execution.
 *
 * Relationship to previous waves:
 *   - It reads lifecycle state from W04 and replacement eligibility from W03.
 *   - It reads trace availability from W05 observation primitives.
 *   - It reads policy identity from W01.
 *
 * Relationship to other files in this wave:
 *   - It wraps TPolicyRealizationBinding.
 *   - It exposes TPolicyRealizationMode and TPolicyTargetKind without exposing
 *     target instances or realizer objects.
 *
 * Relationship to future waves:
 *   - W07 policy graph views may include this view for realization binding nodes.
 *   - W09 TPolicyView may include this view as part of aggregate presentation.
 *   - W10 assignment may use this view to determine descriptor compatibility.
 *
 * Explicit non-responsibilities:
 *   This view does not mutate, execute, resolve, assign, register, or invoke. It
 *   is not a realizer view, not a target view, not a communication binding view,
 *   and not an audit exporter.
 *
 * Current implementation note:
 *   W06 stores a pointer to a binding. A missing pointer is allowed and reports
 *   an incomplete view.
 */
class TPolicyRealizationBindingView final
{
public:
    constexpr TPolicyRealizationBindingView() noexcept = default;
    explicit constexpr TPolicyRealizationBindingView(const TPolicyRealizationBinding* binding) noexcept : binding_(binding) {}

    [[nodiscard]] constexpr bool IsPresent() const noexcept { return binding_ != nullptr; }
    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept { return binding_ != nullptr && binding_->IsStructurallyComplete(); }

    [[nodiscard]] constexpr TPolicyId PolicyId() const noexcept { return binding_ ? binding_->policy_id : TPolicyId{}; }
    [[nodiscard]] constexpr TPolicyFamilyId FamilyId() const noexcept { return binding_ ? binding_->family_id : TPolicyFamilyId{}; }
    [[nodiscard]] constexpr TPolicyRealizationBindingId BindingId() const noexcept { return binding_ ? binding_->descriptor.binding_id : TPolicyRealizationBindingId{}; }
    [[nodiscard]] constexpr TPolicyRealizationMode Mode() const noexcept { return binding_ ? binding_->descriptor.mechanism.mode : TPolicyRealizationMode::unknown; }
    [[nodiscard]] constexpr TPolicyTargetKind TargetKind() const noexcept { return binding_ ? binding_->descriptor.target_kind.kind : TPolicyTargetKind::unknown; }
    [[nodiscard]] constexpr TPolicyLifecycleState LifecycleState() const noexcept { return binding_ ? binding_->lifecycle_state : TPolicyLifecycleState::unknown; }
    [[nodiscard]] constexpr TPolicyReplacementEligibility ReplacementEligibility() const noexcept { return binding_ ? binding_->replacement_eligibility : TPolicyReplacementEligibility::unknown; }
    [[nodiscard]] constexpr bool HasTrace() const noexcept { return binding_ && binding_->HasTrace(); }

private:
    const TPolicyRealizationBinding* binding_{nullptr};
};

} // namespace assembler::ecosystem_governance::policy_type_system

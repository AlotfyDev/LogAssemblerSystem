#pragma once

#include "TViewId.hpp"
#include "TViewScope.hpp"
#include "TViewStability.hpp"
#include "TViewVisibility.hpp"
#include "TViewValidationResult.hpp"

#include <cstdint>
#include <type_traits>

/*
    TReadOnlyViewDescriptor.hpp

    Delivery:
        CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

    Current responsibility:
        Defines an immutable, production-grade descriptor for safe read-only
        projections inside the Circulation Mechanism Engine.

    Production capabilities:
        - immutable view descriptor fields after construction.
        - explicit construction through constexpr constructor/factories.
        - scope/stability/visibility accessors.
        - boundary-safety classification.
        - cross-component visibility classification.
        - diagnostic/test visibility classification.
        - validation function that detects invalid id and unsafe scope/visibility combinations.
        - no mutable handles exposed.

    Architectural role:
        A view is an observation surface. It is not a mutable handle, state owner,
        transition executor, runtime action, report evidence, or bridge/receiver
        contract.

    Explicit non-ownership:
        - Does not mutate viewed state.
        - Does not own viewed state lifetime.
        - Does not emit reports.
        - Does not execute diagnostics export.
        - Does not grant access to private internals.

    Anti-collapse:
        A view may observe state but must not become a state transition API.
        A boundary-safe view must still be read-only and must not expose mutable
        container/slot/registry internals.
*/

namespace assembler {
namespace circulation_mechanism {


class TReadOnlyViewDescriptor final
{
public:
    constexpr TReadOnlyViewDescriptor() noexcept = default;

    constexpr TReadOnlyViewDescriptor(
        TViewId id,
        TViewScope scope,
        TViewStability stability,
        TViewVisibility visibility) noexcept
        : id_(id),
          scope_(scope),
          stability_(stability),
          visibility_(visibility)
    {
    }

    [[nodiscard]] static constexpr TReadOnlyViewDescriptor local_snapshot(TViewId id) noexcept
    {
        return TReadOnlyViewDescriptor{id, TViewScope::local_component, TViewStability::snapshot, TViewVisibility::internal_only};
    }

    [[nodiscard]] static constexpr TReadOnlyViewDescriptor diagnostic_snapshot(TViewId id) noexcept
    {
        return TReadOnlyViewDescriptor{id, TViewScope::diagnostic_only, TViewStability::diagnostic_snapshot, TViewVisibility::diagnostic_visible};
    }

    [[nodiscard]] static constexpr TReadOnlyViewDescriptor boundary_safe_snapshot(TViewId id) noexcept
    {
        return TReadOnlyViewDescriptor{id, TViewScope::boundary_facing, TViewStability::snapshot, TViewVisibility::boundary_safe};
    }

    [[nodiscard]] constexpr TViewId id() const noexcept
    {
        return id_;
    }

    [[nodiscard]] constexpr TViewScope scope() const noexcept
    {
        return scope_;
    }

    [[nodiscard]] constexpr TViewStability stability() const noexcept
    {
        return stability_;
    }

    [[nodiscard]] constexpr TViewVisibility visibility() const noexcept
    {
        return visibility_;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return id_.is_valid();
    }

    [[nodiscard]] constexpr bool is_local_only() const noexcept
    {
        return visibility_ == TViewVisibility::internal_only
            || scope_ == TViewScope::local_component;
    }

    [[nodiscard]] constexpr bool is_boundary_facing() const noexcept
    {
        return scope_ == TViewScope::boundary_facing;
    }

    [[nodiscard]] constexpr bool is_boundary_safe() const noexcept
    {
        return scope_ == TViewScope::boundary_facing
            && visibility_ == TViewVisibility::boundary_safe;
    }

    [[nodiscard]] constexpr bool is_cross_component_visible() const noexcept
    {
        return visibility_ == TViewVisibility::approved_cross_component
            || visibility_ == TViewVisibility::boundary_safe;
    }

    [[nodiscard]] constexpr bool is_diagnostic_visible() const noexcept
    {
        return visibility_ == TViewVisibility::diagnostic_visible
            || scope_ == TViewScope::diagnostic_only;
    }

    [[nodiscard]] constexpr bool is_snapshot() const noexcept
    {
        return stability_ == TViewStability::snapshot
            || stability_ == TViewStability::diagnostic_snapshot;
    }

    [[nodiscard]] constexpr bool is_scoped() const noexcept
    {
        return stability_ == TViewStability::round_scoped
            || stability_ == TViewStability::profile_scoped
            || stability_ == TViewStability::generation_scoped;
    }

    [[nodiscard]] constexpr TViewValidationResult validate() const noexcept
    {
        if (!id_.is_valid())
        {
            return rejected_view_contract(TViewContractIssueKind::invalid_id);
        }

        if (scope_ == TViewScope::boundary_facing && visibility_ != TViewVisibility::boundary_safe)
        {
            return rejected_view_contract(TViewContractIssueKind::boundary_not_safe);
        }

        if (visibility_ == TViewVisibility::boundary_safe && scope_ != TViewScope::boundary_facing)
        {
            return rejected_view_contract(TViewContractIssueKind::scope_visibility_mismatch);
        }

        if (scope_ == TViewScope::diagnostic_only && visibility_ == TViewVisibility::boundary_safe)
        {
            return rejected_view_contract(TViewContractIssueKind::scope_visibility_mismatch);
        }

        return accepted_view_contract();
    }

private:
    TViewId id_{TViewId::invalid()};
    TViewScope scope_{TViewScope::local_component};
    TViewStability stability_{TViewStability::snapshot};
    TViewVisibility visibility_{TViewVisibility::internal_only};
};

static_assert(!std::is_aggregate<TReadOnlyViewDescriptor>::value,
    "TReadOnlyViewDescriptor must not expose mutable aggregate fields.");

} // namespace circulation_mechanism
} // namespace assembler

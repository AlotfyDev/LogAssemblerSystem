#pragma once

#include <cstddef>
#include "TPolicyBuildRequest.hpp"
#include "TPolicyBuildResult.hpp"
#include "TPolicySnapshot.hpp"
#include "TPolicyValidationReport.hpp"
#include "TPolicyView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementPlan.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleSnapshot.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyAuditTrail.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBinding.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBindingView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraph.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/TPolicyTraversalFoundationView.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicy.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicy is the first aggregate object in the Policy Type System. It composes
 *   the foundations from W01 through W08 into a single semantic governing object
 *   that can be viewed, snapshotted, and validated as a policy object. It exists
 *   to represent policy constitution, not to execute policy behavior.
 *
 * Why this file exists in W09:
 *   Earlier waves intentionally avoided a monolithic policy class. After
 *   identity, clauses, safe replacement, lifecycle, observation/audit,
 *   realization binding, graph structure, and traversal foundation vocabulary
 *   exist, W09 is the first safe point to introduce the aggregate that gathers
 *   them into one policy-facing surface.
 *
 * Relationship to previous waves:
 *   - W01: TPolicy owns primitive identity fields.
 *   - W02: TPolicy owns a bounded clause set.
 *   - W03: TPolicy owns a replacement plan and can expose replacement view.
 *   - W04: TPolicy owns a lifecycle snapshot and exposes lifecycle view.
 *   - W05: TPolicy owns a lightweight in-memory audit trail.
 *   - W06: TPolicy owns a realization binding descriptor, not executor.
 *   - W07: TPolicy owns structural graph constitution.
 *   - W08: TPolicy may expose traversal foundation view as data only.
 *
 * Relationship to other files in this wave:
 *   - TPolicyBuildRequest seeds identity construction.
 *   - TPolicyBuildResult reports build/validation outcome.
 *   - TPolicyValidationReport reports aggregate completeness.
 *   - TPolicySnapshot provides copy-safe summary.
 *   - TPolicyView provides read-only aggregate inspection.
 *
 * Relationship to future waves:
 *   - W10 Policy Assignment may reference TPolicy or TPolicyView when creating
 *     assignment descriptors.
 *   - W11 Policy Registry basics may index or catalog TPolicy by identity.
 *   - Later realization/execution layers, if approved, may consume TPolicy but
 *     must remain outside TPolicy itself.
 *
 * Explicit non-responsibilities:
 *   TPolicy does not execute policies, does not realize policies, does not own
 *   target objects, does not invoke targets, does not open communication
 *   bindings, does not traverse graphs, does not schedule orchestration, does
 *   not assign itself, does not register itself globally, and does not export
 *   telemetry or persist audit records.
 *
 * Current implementation note:
 *   W09 intentionally uses bounded fixed-capacity clause storage and compact
 *   value carriers from prior waves. This is a foundation aggregate, not a final
 *   production policy runtime. The opening documentation records the complete
 *   intended architecture even where the code remains a base block.
 */
class TPolicy final
{
public:
    static constexpr std::size_t clause_capacity = 16;

    using clause_set_type = TPolicyClauseSet<clause_capacity>;

    TPolicy() = default;

    explicit TPolicy(TPolicyBuildRequest request) noexcept
        : policy_id_(request.policy_id),
          family_id_(request.family_id),
          version_(request.version),
          scope_(request.scope),
          source_(request.source),
          provenance_(request.provenance),
          graph_(TPolicyGraphId{request.policy_id.value})
    {
    }

    [[nodiscard]] static TPolicy FromRequest(TPolicyBuildRequest request) noexcept
    {
        return TPolicy{request};
    }

    [[nodiscard]] constexpr TPolicyId PolicyId() const noexcept { return policy_id_; }
    [[nodiscard]] constexpr TPolicyFamilyId FamilyId() const noexcept { return family_id_; }
    [[nodiscard]] constexpr TPolicyVersion Version() const noexcept { return version_; }
    [[nodiscard]] constexpr TPolicyScope Scope() const noexcept { return scope_; }
    [[nodiscard]] constexpr TPolicySource Source() const noexcept { return source_; }
    [[nodiscard]] constexpr TPolicyProvenance Provenance() const noexcept { return provenance_; }

    [[nodiscard]] constexpr const clause_set_type& Clauses() const noexcept { return clauses_; }
    [[nodiscard]] constexpr const TPolicyReplacementPlan& ReplacementPlan() const noexcept { return replacement_plan_; }
    [[nodiscard]] constexpr const TPolicyLifecycleSnapshot& LifecycleSnapshot() const noexcept { return lifecycle_; }
    [[nodiscard]] const TPolicyAuditTrail& AuditTrail() const noexcept { return audit_trail_; }
    [[nodiscard]] constexpr const TPolicyRealizationBinding& RealizationBinding() const noexcept { return realization_binding_; }
    [[nodiscard]] constexpr const TPolicyGraph& Graph() const noexcept { return graph_; }
    [[nodiscard]] constexpr TPolicyTraversalFoundationView TraversalFoundation() const noexcept { return traversal_; }

    [[nodiscard]] constexpr bool HasMinimumIdentity() const noexcept
    {
        return policy_id_.IsValid() && family_id_.IsValid() && !version_.IsZero() && IsSpecified(scope_);
    }

    [[nodiscard]] constexpr bool HasUsableClauses() const noexcept
    {
        return clauses_.HasUsableClause();
    }

    [[nodiscard]] constexpr bool HasReplacementStructure() const noexcept
    {
        return replacement_plan_.IsStructurallyUsable();
    }

    [[nodiscard]] constexpr bool HasLifecycleStructure() const noexcept
    {
        return lifecycle_.IsStructurallyUsable();
    }

    [[nodiscard]] bool HasObservationStructure() const noexcept
    {
        return !audit_trail_.Empty();
    }

    [[nodiscard]] constexpr bool HasRealizationBinding() const noexcept
    {
        return realization_binding_.IsStructurallyComplete();
    }

    [[nodiscard]] constexpr bool HasGraphStructure() const noexcept
    {
        return graph_.graph_id.IsValid() && graph_.node_count > 0;
    }

    [[nodiscard]] constexpr bool HasTraversalFoundation() const noexcept
    {
        return traversal_.IsNonEmpty();
    }

    bool AddClause(const TPolicyClause& clause) noexcept
    {
        return clauses_.Add(clause);
    }

    void SetReplacementPlan(TPolicyReplacementPlan plan) noexcept
    {
        replacement_plan_ = plan;
    }

    void SetLifecycleSnapshot(TPolicyLifecycleSnapshot snapshot) noexcept
    {
        lifecycle_ = snapshot;
    }

    void AddAuditMarker(TPolicyAuditMarker marker)
    {
        audit_trail_.Add(marker);
    }

    void SetRealizationBinding(TPolicyRealizationBinding binding) noexcept
    {
        realization_binding_ = binding;
    }

    void SetGraph(TPolicyGraph graph) noexcept
    {
        graph_ = graph;
    }

    void SetTraversalFoundation(TPolicyTraversalFoundationView traversal) noexcept
    {
        traversal_ = traversal;
    }

    [[nodiscard]] TPolicyValidationReport Validate() const noexcept
    {
        TPolicyValidationReport report{};
        report.identity_present = HasMinimumIdentity();
        report.clauses_present = HasUsableClauses();
        report.replacement_present = HasReplacementStructure();
        report.lifecycle_present = HasLifecycleStructure();
        report.observation_present = HasObservationStructure();
        report.realization_binding_present = HasRealizationBinding();
        report.graph_present = HasGraphStructure();
        report.graph_minimum_valid = graph_.IsStructurallyValidMinimum();
        report.traversal_foundation_present = HasTraversalFoundation();
        report.issue = TPolicyIssue{report.Status(), report.MissingMask()};
        return report;
    }

    [[nodiscard]] TPolicyBuildResult BuildResult() const noexcept
    {
        return TPolicyBuildResult::FromValidation(Validate());
    }

    [[nodiscard]] TPolicySnapshot Snapshot() const noexcept
    {
        return TPolicySnapshot{
            policy_id_,
            family_id_,
            version_,
            scope_,
            lifecycle_.State(),
            replacement_plan_.eligibility,
            clauses_.Size(),
            audit_trail_.Count(),
            graph_.node_count,
            graph_.edge_count,
            traversal_.channel_count,
            Validate().IsStructurallyComplete()};
    }

    [[nodiscard]] TPolicyView View() const noexcept
    {
        TPolicyView view{};
        view.snapshot = Snapshot();
        view.validation = Validate();
        view.lifecycle = TPolicyLifecycleView{lifecycle_};
        view.replacement = TPolicyReplacementView::FromPlan(replacement_plan_);
        view.realization = TPolicyRealizationBindingView{&realization_binding_};
        view.graph = graph_.View();
        view.traversal = traversal_;
        return view;
    }

private:
    TPolicyId policy_id_{};
    TPolicyFamilyId family_id_{};
    TPolicyVersion version_{};
    TPolicyScope scope_{TPolicyScope::unspecified};
    TPolicySource source_{};
    TPolicyProvenance provenance_{};
    clause_set_type clauses_{};
    TPolicyReplacementPlan replacement_plan_{};
    TPolicyLifecycleSnapshot lifecycle_{};
    TPolicyAuditTrail audit_trail_{};
    TPolicyRealizationBinding realization_binding_{};
    TPolicyGraph graph_{};
    TPolicyTraversalFoundationView traversal_{};
};

} // namespace assembler::ecosystem_governance::policy_type_system

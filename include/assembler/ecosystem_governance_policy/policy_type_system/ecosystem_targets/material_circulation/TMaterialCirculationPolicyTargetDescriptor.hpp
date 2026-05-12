#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W26_MaterialCirculation_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / material_circulation
 *
 * Architectural boundary:
 *   W26 continues Phase E -- Ecosystem Integration by introducing
 *   policy-target descriptors for the reusable Material Circulation domain.
 *   It maps ecosystem-governance policy vocabulary onto material-circulation
 *   target categories such as admission, slot lifecycle, container moderation,
 *   bundle coordination, waiting-list behavior, receiving/delivery rounds,
 *   reference precalculation, dispatcher behavior, and output-boundary handoff.
 *   The wave is integration-facing but remains descriptive: it does not
 *   implement material circulation mechanics, mutate slots, run round managers,
 *   dispatch payloads, activate assignments, bind communication surfaces, or
 *   realize policies.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and scope vocabulary.
 *   - W06 supplies descriptor-only target-kind language.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies policy-family and scope profiles.
 *   - W13 supplies target-capability descriptors and capability sets.
 *   - W14 supplies family-target compatibility rule/report vocabulary.
 *   - W15 supplies assignment lifecycle/conflict vocabulary.
 *   - W16/W17 supply source/publication and registry-versioning views.
 *   - W18-W20 supply realization contract, runtime readiness, and runtime plan
 *     pre-execution artifacts.
 *   - W21-W24 supply realizer-facing, session, execution-plan, and engine
 *     skeleton layers without production execution.
 *   - W25 introduced the log_level_api policy-target slice; W26 mirrors that
 *     integration pattern for material_circulation.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies material-circulation policy families such as
 *   material admission, slot lifecycle, waiting list, receiving round,
 *   delivery round, dispatcher, and reference precalculation policies.
 *   EG-POL-ARCH-002 identifies material-circulation target kinds and required
 *   target capabilities. EG-POL-ARCH-003 requires explicit compatibility
 *   between policy families, target kinds, target scopes, lifecycle,
 *   replacement, and observation expectations before assignment or realization.
 *   W26 creates a conservative C++ integration skeleton for that material
 *   circulation slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement material circulation runtime behavior, slot
 *   mutation, slots-container storage, waiting-list movement, round-manager
 *   algorithms, dispatcher execution, reference-precalculation algorithms,
 *   assignment activation, authority roles, source publication, registry
 *   persistence, realization contracts, runtime execution, TPolicyExecutor,
 *   direct target invocation, communication binding, add-on execution,
 *   telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 */
/*
 * File responsibility:
 *   TMaterialCirculationPolicyTargetDescriptor describes one material
 *   circulation target as a policy-governable target descriptor. It bridges the
 *   material_circulation-local target taxonomy to the global target-kind
 *   vocabulary without owning a concrete target instance or invoking behavior.
 */
struct TMaterialCirculationPolicyTargetDescriptor final
{
    std::string target_id{};
    TMaterialCirculationPolicyTargetKind local_kind{TMaterialCirculationPolicyTargetKind::unknown};
    TPolicyTargetKind global_kind{TPolicyTargetKind::material_circulation_component};
    TPolicyScopePath scope_path{};
    bool hot_path{true};
    bool replacement_sensitive{true};
    bool observation_required{true};
    bool realization_capable{false};
    std::string note{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return !target_id.empty() &&
               IsKnownMaterialCirculationPolicyTargetKind(local_kind) &&
               IsKnown(global_kind) &&
               scope_path.IsSpecified();
    }

    [[nodiscard]] bool RequiresReplacementDiscipline() const noexcept
    {
        return replacement_sensitive || IsReplacementSensitiveMaterialTarget(local_kind);
    }

    [[nodiscard]] bool IsRuntimeCoordinationTarget() const noexcept
    {
        return IsRuntimeStructureTarget(local_kind) || IsCoordinationTarget(local_kind);
    }

    [[nodiscard]] static TMaterialCirculationPolicyTargetDescriptor Make(
        std::string id,
        TMaterialCirculationPolicyTargetKind kind,
        TPolicyScopePath scope,
        bool realization = false)
    {
        TMaterialCirculationPolicyTargetDescriptor descriptor;
        descriptor.target_id = std::move(id);
        descriptor.local_kind = kind;
        descriptor.scope_path = std::move(scope);
        descriptor.realization_capable = realization;
        descriptor.replacement_sensitive = IsReplacementSensitiveMaterialTarget(kind);
        descriptor.hot_path = kind != TMaterialCirculationPolicyTargetKind::policy_assignment_boundary;
        return descriptor;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

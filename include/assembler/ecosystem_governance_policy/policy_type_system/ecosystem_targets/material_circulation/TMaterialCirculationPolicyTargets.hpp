#pragma once

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyFamilyTargetRuleSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyTargetIntegrationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyTargetRegistryView.hpp"

#include <sstream>

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
 *   TMaterialCirculationPolicyTargets is the W26 facade for describing
 *   material_circulation policy targets, their capability profiles, and their
 *   compatibility-matrix rules. It can inspect descriptor completeness but does
 *   not assign, realize, or invoke policies or targets.
 */
struct TMaterialCirculationPolicyTargets final
{
    TMaterialCirculationPolicyTargetRegistryView registry_view{};
    TMaterialCirculationPolicyFamilyTargetRuleSet rule_set{};

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        return registry_view.IsCompleteForCoreMaterialTargets() && !rule_set.IsEmpty();
    }

    [[nodiscard]] TMaterialCirculationPolicyTargetIntegrationReport Inspect() const
    {
        TMaterialCirculationPolicyTargetIntegrationReport report;
        report.described_targets = registry_view.targets.size();
        report.compatibility_rules = rule_set.matrix.rules.size();
        if (!registry_view.IsCompleteForCoreMaterialTargets())
        {
            report.AddIssue(TMaterialCirculationPolicyTargetIntegrationIssueSeverity::blocking,
                            TMaterialCirculationPolicyTargetIntegrationIssueKind::missing_target,
                            "material_circulation target registry view is missing one or more core target descriptors");
        }
        if (rule_set.IsEmpty())
        {
            report.AddIssue(TMaterialCirculationPolicyTargetIntegrationIssueSeverity::blocking,
                            TMaterialCirculationPolicyTargetIntegrationIssueKind::missing_compatibility_rule,
                            "material_circulation policy-target compatibility rule set is empty");
        }
        return report;
    }


    [[nodiscard]] static TPolicyScopePath MakeScopePath(const char* text)
    {
        TPolicyScopePath path{TPolicyScope::component};
        std::stringstream stream{text};
        std::string segment;
        while (std::getline(stream, segment, '.'))
        {
            path.Push(segment);
        }
        return path;
    }

    [[nodiscard]] static TMaterialCirculationPolicyTargets DefaultMaterialCirculationTargets()
    {
        TMaterialCirculationPolicyTargets targets;
        auto add = [&](const char* id, TMaterialCirculationPolicyTargetKind kind, const char* scope, bool realization) {
            auto descriptor = TMaterialCirculationPolicyTargetDescriptor::Make(
                id,
                kind,
                MakeScopePath(scope),
                realization);
            targets.registry_view.Add(TMaterialCirculationPolicyTargetCapabilityProfile::MakeDefault(std::move(descriptor)));
        };
        add("material_admission", TMaterialCirculationPolicyTargetKind::admission, "system.material_circulation.admission", false);
        add("material_slot", TMaterialCirculationPolicyTargetKind::slot, "system.material_circulation.runtime.slot", true);
        add("slots_container", TMaterialCirculationPolicyTargetKind::slots_container, "system.material_circulation.runtime.slots_container", true);
        add("waiting_list", TMaterialCirculationPolicyTargetKind::waiting_list, "system.material_circulation.runtime.waiting_list", true);
        add("container_moderator", TMaterialCirculationPolicyTargetKind::container_moderator, "system.material_circulation.runtime.container_moderator", true);
        add("bundle_agent", TMaterialCirculationPolicyTargetKind::bundle_agent, "system.material_circulation.runtime.bundle_agent", true);
        add("receiving_round_manager", TMaterialCirculationPolicyTargetKind::receiving_round_manager, "system.material_circulation.admission.receiving_round_manager", true);
        add("delivery_round_manager", TMaterialCirculationPolicyTargetKind::delivery_round_manager, "system.material_circulation.delivery.delivery_round_manager", true);
        add("dispatcher", TMaterialCirculationPolicyTargetKind::dispatcher, "system.material_circulation.delivery.dispatcher", true);
        add("reference_precalculator", TMaterialCirculationPolicyTargetKind::reference_precalculator, "system.material_circulation.runtime.reference_precalculator", false);
        add("output_boundary", TMaterialCirculationPolicyTargetKind::output_boundary, "system.material_circulation.delivery.output_boundary", false);
        targets.rule_set = TMaterialCirculationPolicyFamilyTargetRuleSet::DefaultMaterialCirculationRules();
        return targets;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

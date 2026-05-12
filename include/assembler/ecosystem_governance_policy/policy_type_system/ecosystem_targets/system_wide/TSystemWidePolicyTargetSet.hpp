#pragma once

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargets.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurface.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargets.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyTargets.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W29_System_Wide_Policy_Integration_Skeleton
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / system_wide
 *
 * Architectural boundary:
 *   W29 closes the first Phase E ecosystem-integration slice by introducing a
 *   system-wide policy integration skeleton. It composes the descriptive
 *   target surfaces introduced in W25, W26, W27, and W28 and names the
 *   governance path from published policy metadata, assignment identity,
 *   target descriptors, runtime-readiness evidence, runtime plan, and
 *   realizer-facing identity into one inspectable integration artifact.
 *
 *   This wave is explicitly non-executing. It does not activate assignments,
 *   invoke a realizer, run an engine, mutate targets, bind communication
 *   participants, move material through material circulation, call add-ons, or
 *   persist registry records. It only checks whether the major ecosystem
 *   target slices are present and represented in a conservative, boundary-safe
 *   C++17 form.
 *
 * Relationship to prior waves:
 *   - W01-W11 define the base policy type system, aggregate, assignment, and
 *     registry basics.
 *   - W12-W17 add family/scope, target capabilities, compatibility, assignment
 *     lifecycle, source/publication, and registry versioning views.
 *   - W18-W20 add realization contract, runtime readiness, and runtime plan
 *     pre-execution artifacts.
 *   - W21-W24 add realizer interface, realization session, execution-plan, and
 *     realization-engine skeleton layers without production runtime execution.
 *   - W25-W28 add the log_level_api, material_circulation,
 *     communication_context, and add-on ecosystem target slices.
 *
 * Relationship to Phase A architecture:
 *   Phase A required a system-wide policy-to-target matrix and compliance gate
 *   before any realizer/runtime path. W29 is not that final compliance engine;
 *   it is a concrete integration skeleton that proves the major descriptive
 *   surfaces can be composed without collapsing publication into assignment,
 *   assignment into realization, realization into execution, target kind into
 *   target instance, or registry lookup into service location.
 *
 * Explicit non-responsibilities:
 *   This file does not implement runtime execution, target invocation, target
 *   mutation, policy assignment activation, persistent registry storage,
 *   source parsing, communication binding, material circulation runtime
 *   behavior, add-on execution, telemetry export, logging, or database
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative header-only C++17 foundation. The opening
 *   documentation describes the complete architectural responsibility while
 *   the code remains compact value carriers and inspection helpers for compile
 *   smoke validation.
 */

/*
 * File responsibility:
 *   TSystemWidePolicyTargetSet composes the four Phase E target slices into one
 *   descriptive system-wide set. It does not merge their runtimes and does not
 *   turn any descriptor into a live target instance.
 */
struct TSystemWidePolicyTargetSet final
{
    TLogLevelApiPolicyTargets log_level_api{};
    TMaterialCirculationPolicyTargets material_circulation{};
    TCommunicationContextPolicySurface communication_context{};
    TAddonPolicyTargets addons{};

    [[nodiscard]] bool HasAllCoreSlices() const noexcept
    {
        return log_level_api.IsStructurallyComplete() &&
               material_circulation.IsStructurallyComplete() &&
               communication_context.IsStructurallyComplete() &&
               addons.IsStructurallyComplete();
    }

    [[nodiscard]] static TSystemWidePolicyTargetSet Default()
    {
        TSystemWidePolicyTargetSet set{};
        set.log_level_api = TLogLevelApiPolicyTargets::Default();
        set.material_circulation = TMaterialCirculationPolicyTargets::DefaultMaterialCirculationTargets();
        set.communication_context = TCommunicationContextPolicySurface::Default();
        set.addons = TAddonPolicyTargets::Default();
        return set;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

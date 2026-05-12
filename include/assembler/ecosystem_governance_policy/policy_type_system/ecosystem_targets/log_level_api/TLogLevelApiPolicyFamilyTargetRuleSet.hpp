#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityMatrix.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyFamilyTargetRuleSet.hpp

 * Wave: EG-POL-W25_LogLevelApi_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / log_level_api
 *
 * Architectural boundary:
 *   W25 opens Phase E -- Ecosystem Integration by introducing policy-target
 *   descriptors for the Log Level API preparation domain. The wave maps
 *   governance-level policy vocabulary onto log-level API target categories
 *   such as validation, metadata injection, timestamp stabilization, envelope
 *   assembly, and API-facade admission. It is integration-facing but remains
 *   descriptive: it does not implement the Log Level API, validate content,
 *   inject metadata, stabilize timestamps, assemble envelopes, bind
 *   communication surfaces, assign policies, or realize policies.
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
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies preparation policy families such as validation,
 *   metadata injection, timestamp stabilization, and envelope assembly.
 *   EG-POL-ARCH-002 identifies preparation targets such as validator,
 *   metadata injector, timestamp stabilizer, envelope assembler, and API facade.
 *   EG-POL-ARCH-003 requires explicit compatibility between families and target
 *   capabilities before assignment or realization. W25 creates a conservative
 *   C++ integration skeleton for that log_level_api slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement log_level_api runtime behavior, content
 *   validation, envelope filling, metadata mutation, timestamp algorithms,
 *   policy assignment activation, authority roles, source publication,
 *   registry persistence, realization contracts, runtime execution,
 *   TPolicyExecutor, direct target invocation, material circulation,
 *   communication binding, add-on execution, telemetry, logging, or database
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 * File responsibility:
 *   TLogLevelApiPolicyFamilyTargetRuleSet provides the log_level_api-oriented compatibility rows used to evaluate preparation/admission/diagnostic policy families against the coarse log_level_api ecosystem target kind. It is not an assignment engine and not a realizer.
 */

struct TLogLevelApiPolicyFamilyTargetRuleSet final
{
    TPolicyFamilyCompatibilityMatrix matrix{};

    [[nodiscard]] bool IsEmpty() const noexcept { return matrix.rules.empty(); }

    void AddPreparationRule(std::string rule_id, TPolicyFamilyKind family_kind)
    {
        TPolicyFamilyCompatibilityRule rule{};
        rule.rule_id = std::move(rule_id);
        rule.policy_family_kind = family_kind;
        rule.target_kind = TPolicyTargetKind::log_level_api_component;
        rule.allowed_scopes = {TPolicyScope::domain, TPolicyScope::component, TPolicyScope::boundary};
        rule.required_capabilities = {
            TPolicyTargetCapabilityKind::accepts_policy_assignment,
            TPolicyTargetCapabilityKind::supports_readiness_check,
            TPolicyTargetCapabilityKind::declares_target_kind,
            TPolicyTargetCapabilityKind::declares_capability_set
        };
        rule.recommended_capabilities = {
            TPolicyTargetCapabilityKind::reports_lifecycle_state,
            TPolicyTargetCapabilityKind::supports_policy_observation_record
        };
        rule.realization_mode = TPolicyRealizationMode::descriptive_only;
        rule.lifecycle_required = true;
        rule.replacement_required = false;
        rule.observation_required = true;
        matrix.AddRule(std::move(rule));
    }

    [[nodiscard]] static TLogLevelApiPolicyFamilyTargetRuleSet Default()
    {
        TLogLevelApiPolicyFamilyTargetRuleSet rules{};
        rules.AddPreparationRule("log_level_api.preparation.validation", TPolicyFamilyKind::preparation);
        rules.AddPreparationRule("log_level_api.admission.api_facade", TPolicyFamilyKind::admission);
        rules.AddPreparationRule("log_level_api.diagnostic.observation", TPolicyFamilyKind::diagnostic);
        return rules;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system

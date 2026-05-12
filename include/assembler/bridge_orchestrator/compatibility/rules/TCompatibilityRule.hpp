#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/compatibility/issues/TCompatibilityIssue.hpp"

/**
 * @file TCompatibilityRule.hpp
 * @brief Named compatibility rule descriptor and primitive checks.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable rule descriptor for compatibility checks;
 * - future support for rule catalogs, validation packs, and rule-to-source
 *   traceability;
 * - deterministic primitive rule functions for binding model evaluation.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - rule descriptor value;
 * - rule-kind taxonomy;
 * - primitive static checks for W06 binding state.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol stepping or bridge orchestration;
 * - endpoint-domain validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - plugin-based rule engine or endpoint-specific rule loading.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Compatibility model headers may depend on W01 carriers/results, W03
 * participant views, W04 channel topology, W05 obligation-surface views, and
 * W06 binding model declarations. They must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TCompatibilityRuleKind
    {
        unknown,
        require_valid_channel,
        require_valid_surface_pair,
        require_primary_placement_flow,
        require_valid_binding_profile,
        require_compatible_binding_report,
        require_usable_binding_status,
        require_authority_safe_boundary
    };

    struct TCompatibilityRule final
    {
        std::uint32_t rule_id{0u};
        TCompatibilityRuleKind kind{TCompatibilityRuleKind::unknown};
        TCompatibilityDimension dimension{TCompatibilityDimension::unknown};
        TCompatibilitySeverity failure_severity{TCompatibilitySeverity::blocking};
        std::string_view code{};
        std::string_view description{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return rule_id != 0u
                && kind != TCompatibilityRuleKind::unknown
                && dimension != TCompatibilityDimension::unknown;
        }

        [[nodiscard]] constexpr TCompatibilityIssue check(
            const TBinding& binding) const noexcept
        {
            if (!is_valid())
            {
                return TCompatibilityIssue::fatal(
                    TCompatibilityDimension::unknown,
                    "compatibility.rule.invalid",
                    "compatibility rule descriptor is invalid",
                    binding.correlation);
            }

            bool passed = false;

            switch (kind)
            {
                case TCompatibilityRuleKind::require_valid_channel:
                    passed = binding.channel.is_valid() && binding.channel.is_declared();
                    break;

                case TCompatibilityRuleKind::require_valid_surface_pair:
                    passed = binding.surface_pair.is_valid();
                    break;

                case TCompatibilityRuleKind::require_primary_placement_flow:
                    passed = binding.surface_pair.supports_primary_placement_flow();
                    break;

                case TCompatibilityRuleKind::require_valid_binding_profile:
                    passed = binding.profile.is_valid();
                    break;

                case TCompatibilityRuleKind::require_compatible_binding_report:
                    passed = binding.compatibility.is_compatible();
                    break;

                case TCompatibilityRuleKind::require_usable_binding_status:
                    passed = is_usable_binding_status(binding.status);
                    break;

                case TCompatibilityRuleKind::require_authority_safe_boundary:
                    passed = binding.channel.is_valid()
                        && binding.surface_pair.is_valid()
                        && binding.channel.channel_id != 0u;
                    break;

                case TCompatibilityRuleKind::unknown:
                    passed = false;
                    break;
            }

            if (passed)
            {
                return TCompatibilityIssue::pass(
                    dimension,
                    code,
                    "compatibility rule passed",
                    binding.correlation);
            }

            if (failure_severity == TCompatibilitySeverity::warning)
            {
                return TCompatibilityIssue::warn(
                    dimension,
                    code,
                    description,
                    binding.correlation);
            }

            if (failure_severity == TCompatibilitySeverity::fatal)
            {
                return TCompatibilityIssue::fatal(
                    dimension,
                    code,
                    description,
                    binding.correlation);
            }

            return TCompatibilityIssue::block(
                dimension,
                code,
                description,
                binding.correlation);
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TCompatibilityRuleKind kind) noexcept
    {
        switch (kind)
        {
            case TCompatibilityRuleKind::unknown: return "unknown";
            case TCompatibilityRuleKind::require_valid_channel: return "require_valid_channel";
            case TCompatibilityRuleKind::require_valid_surface_pair: return "require_valid_surface_pair";
            case TCompatibilityRuleKind::require_primary_placement_flow: return "require_primary_placement_flow";
            case TCompatibilityRuleKind::require_valid_binding_profile: return "require_valid_binding_profile";
            case TCompatibilityRuleKind::require_compatible_binding_report: return "require_compatible_binding_report";
            case TCompatibilityRuleKind::require_usable_binding_status: return "require_usable_binding_status";
            case TCompatibilityRuleKind::require_authority_safe_boundary: return "require_authority_safe_boundary";
        }

        return "unknown";
    }
}

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "assembler/communication_context/compatibility/matrix/TCompatibilityMatrix.hpp"
#include "assembler/communication_context/compatibility/rules/TCompatibilityRule.hpp"

/**
 * @file TCompatibilityRuleSet.hpp
 * @brief Fixed compatibility rule set.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable set of compatibility rules for bridge setup validation;
 * - deterministic header-only evaluation path;
 * - future rule-set specialization for binding classes, channels, policies,
 *   protocols, and concrete integration surfaces.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - fixed-capacity rule set;
 * - add and evaluate helpers;
 * - strict binding rule-set factory aligned with W06 declaration model.
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
 * - runtime plugin rule discovery or mutable global rule registry.
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
    template <std::size_t Capacity>
    struct TCompatibilityRuleSet final
    {
        std::array<TCompatibilityRule, Capacity> rules{};
        std::size_t rule_count{0u};

        constexpr bool add(TCompatibilityRule rule) noexcept
        {
            if (rule_count >= Capacity)
            {
                return false;
            }

            rules[rule_count] = rule;
            ++rule_count;
            return true;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return rule_count == 0u;
        }

        [[nodiscard]] constexpr bool valid() const noexcept
        {
            if (rule_count == 0u)
            {
                return false;
            }

            for (std::size_t index = 0u; index < rule_count; ++index)
            {
                if (!rules[index].is_valid())
                {
                    return false;
                }
            }

            return true;
        }

        template <std::size_t MatrixCapacity>
        [[nodiscard]] constexpr TCompatibilityMatrix<MatrixCapacity> evaluate(
            const TBinding& binding) const noexcept
        {
            TCompatibilityMatrix<MatrixCapacity> matrix{};

            for (std::size_t index = 0u; index < rule_count; ++index)
            {
                matrix.add(rules[index].check(binding));
            }

            return matrix;
        }

        [[nodiscard]] static constexpr TCompatibilityRuleSet<7> strict_binding_rules() noexcept
        {
            TCompatibilityRuleSet<7> set{};

            set.add(TCompatibilityRule{
                1u,
                TCompatibilityRuleKind::require_valid_channel,
                TCompatibilityDimension::channel_topology,
                TCompatibilitySeverity::blocking,
                "compatibility.channel.valid",
                "binding requires a valid declared channel"
            });

            set.add(TCompatibilityRule{
                2u,
                TCompatibilityRuleKind::require_valid_surface_pair,
                TCompatibilityDimension::obligation_surfaces,
                TCompatibilitySeverity::blocking,
                "compatibility.surface_pair.valid",
                "binding requires a valid obligation surface pair"
            });

            set.add(TCompatibilityRule{
                3u,
                TCompatibilityRuleKind::require_primary_placement_flow,
                TCompatibilityDimension::placement_flow,
                TCompatibilitySeverity::blocking,
                "compatibility.placement_flow.primary",
                "binding requires primary placement-flow compatibility"
            });

            set.add(TCompatibilityRule{
                4u,
                TCompatibilityRuleKind::require_valid_binding_profile,
                TCompatibilityDimension::binding_profile,
                TCompatibilitySeverity::blocking,
                "compatibility.binding_profile.valid",
                "binding requires a valid binding profile"
            });

            set.add(TCompatibilityRule{
                5u,
                TCompatibilityRuleKind::require_compatible_binding_report,
                TCompatibilityDimension::binding_status,
                TCompatibilitySeverity::blocking,
                "compatibility.binding_report.compatible",
                "binding requires a compatible W06 compatibility report"
            });

            set.add(TCompatibilityRule{
                6u,
                TCompatibilityRuleKind::require_usable_binding_status,
                TCompatibilityDimension::binding_status,
                TCompatibilitySeverity::blocking,
                "compatibility.binding_status.usable",
                "binding requires compatible or materialized status"
            });

            set.add(TCompatibilityRule{
                7u,
                TCompatibilityRuleKind::require_authority_safe_boundary,
                TCompatibilityDimension::authority_boundary,
                TCompatibilitySeverity::blocking,
                "compatibility.authority_boundary.safe",
                "binding must preserve a declared channel and obligation-surface boundary"
            });

            return set;
        }
    };
}

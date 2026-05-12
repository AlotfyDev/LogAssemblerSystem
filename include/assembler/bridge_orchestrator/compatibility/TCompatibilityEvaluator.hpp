#pragma once

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/compatibility/matrix/TCompatibilityMatrix.hpp"
#include "assembler/communication_context/compatibility/rules/TCompatibilityRuleSet.hpp"
#include "assembler/communication_context/compatibility/views/TCompatibilityView.hpp"

/**
 * @file TCompatibilityEvaluator.hpp
 * @brief Compatibility evaluator facade.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - authoritative compatibility-evaluation facade for binding setup;
 * - future bridge between rule catalogs, validation reports, binding registries,
 *   session materialization gates, and protocol readiness checks;
 * - deterministic interface that keeps evaluation separate from execution.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - strict binding evaluation against W06 binding declarations;
 * - matrix and view construction helpers;
 * - no dynamic allocation and no endpoint invocation.
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
 * - bridge execution, session factory, or endpoint adapter invocation.
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
    struct TCompatibilityEvaluator final
    {
        [[nodiscard]] static constexpr TCompatibilityRuleSet<7> strict_binding_rules() noexcept
        {
            return TCompatibilityRuleSet<7>::strict_binding_rules();
        }

        [[nodiscard]] static constexpr TCompatibilityMatrix<8> evaluate_strict_binding(
            const TBinding& binding) noexcept
        {
            const auto rules = strict_binding_rules();
            return rules.template evaluate<8>(binding);
        }

        [[nodiscard]] static constexpr bool is_strictly_compatible(
            const TBinding& binding) noexcept
        {
            const auto matrix = evaluate_strict_binding(binding);
            return binding.is_compatible()
                && matrix.compatible();
        }

        [[nodiscard]] static constexpr TCompatibilityView view_strict_binding(
            const TBinding& binding) noexcept
        {
            const auto matrix = evaluate_strict_binding(binding);

            return TCompatibilityView::from_matrix(
                binding.view(),
                matrix,
                matrix.compatible()
                    ? "binding is strictly compatible"
                    : "binding is not strictly compatible");
        }
    };
}

#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bindings/binding_views/TBindingView.hpp"
#include "assembler/communication_context/compatibility/matrix/TCompatibilityMatrix.hpp"

/**
 * @file TCompatibilityView.hpp
 * @brief Read-only compatibility evaluation projection.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - public compatibility projection for bridge setup diagnostics;
 * - future diagnostic view for compatibility reports, binding registries,
 *   sessions, and bridge setup plans;
 * - stable view that does not expose endpoint internals or execution handles.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - binding view summary;
 * - issue counts and compatibility status;
 * - diagnostic display name and report summary.
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
 * - mutable evaluator state or endpoint execution handles.
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
    struct TCompatibilityView final
    {
        TBindingView binding{};
        bool compatible{false};
        std::size_t issue_count{0u};
        std::size_t blocking_issue_count{0u};
        std::size_t warning_issue_count{0u};
        std::string_view summary{};

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return compatible && blocking_issue_count == 0u;
        }

        [[nodiscard]] constexpr bool needs_review() const noexcept
        {
            return warning_issue_count > 0u && blocking_issue_count == 0u;
        }

        template <std::size_t Capacity>
        [[nodiscard]] static constexpr TCompatibilityView from_matrix(
            TBindingView binding_view,
            const TCompatibilityMatrix<Capacity>& matrix,
            std::string_view text = "compatibility evaluation complete") noexcept
        {
            return TCompatibilityView{
                binding_view,
                matrix.compatible(),
                matrix.issue_count,
                matrix.blocking_count(),
                matrix.warning_count(),
                text
            };
        }
    };
}

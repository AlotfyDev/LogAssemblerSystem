#pragma once

#include <string_view>

/**
 * @file TCompatibilitySeverity.hpp
 * @brief Compatibility issue severity model.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable issue severity levels for compatibility diagnostics;
 * - distinction between blocking incompatibility and advisory warnings;
 * - future mapping into validation reports, CI checks, and bridge setup
 *   diagnostics.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - enum class `TCompatibilitySeverity`;
 * - constexpr blocking helper;
 * - textual conversion helper.
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
 * - runtime logging or telemetry emission.
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
    enum class TCompatibilitySeverity
    {
        none,
        info,
        warning,
        blocking,
        fatal
    };

    [[nodiscard]] constexpr bool is_blocking(
        TCompatibilitySeverity severity) noexcept
    {
        return severity == TCompatibilitySeverity::blocking
            || severity == TCompatibilitySeverity::fatal;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TCompatibilitySeverity severity) noexcept
    {
        switch (severity)
        {
            case TCompatibilitySeverity::none: return "none";
            case TCompatibilitySeverity::info: return "info";
            case TCompatibilitySeverity::warning: return "warning";
            case TCompatibilitySeverity::blocking: return "blocking";
            case TCompatibilitySeverity::fatal: return "fatal";
        }

        return "none";
    }
}

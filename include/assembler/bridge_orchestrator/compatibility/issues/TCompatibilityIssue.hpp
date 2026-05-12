#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/compatibility/dimensions/TCompatibilityDimension.hpp"
#include "assembler/communication_context/compatibility/severity/TCompatibilitySeverity.hpp"

/**
 * @file TCompatibilityIssue.hpp
 * @brief Single compatibility diagnostic issue.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - diagnostic record for one compatibility finding;
 * - stable dimension, severity, code, explanation, and correlation data;
 * - future suitability for matrix rows, validation reports, bridge setup logs,
 *   and CI-style review artifacts.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - lightweight constexpr value object;
 * - blocking/non-blocking helpers;
 * - static factories for pass, warning, block, and fatal diagnostics.
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
 * - exception throwing or runtime log persistence.
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
    struct TCompatibilityIssue final
    {
        TCompatibilityDimension dimension{TCompatibilityDimension::unknown};
        TCompatibilitySeverity severity{TCompatibilitySeverity::none};
        std::string_view code{};
        std::string_view message{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_present() const noexcept
        {
            return severity != TCompatibilitySeverity::none;
        }

        [[nodiscard]] constexpr bool is_blocking_issue() const noexcept
        {
            return is_blocking(severity);
        }

        [[nodiscard]] constexpr bool is_clean() const noexcept
        {
            return !is_present();
        }

        [[nodiscard]] static constexpr TCompatibilityIssue pass(
            TCompatibilityDimension checked_dimension,
            std::string_view issue_code = "compatibility.pass",
            std::string_view text = "compatibility check passed",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TCompatibilityIssue{
                checked_dimension,
                TCompatibilitySeverity::none,
                issue_code,
                text,
                token
            };
        }

        [[nodiscard]] static constexpr TCompatibilityIssue warn(
            TCompatibilityDimension checked_dimension,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TCompatibilityIssue{
                checked_dimension,
                TCompatibilitySeverity::warning,
                issue_code,
                text,
                token
            };
        }

        [[nodiscard]] static constexpr TCompatibilityIssue block(
            TCompatibilityDimension checked_dimension,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TCompatibilityIssue{
                checked_dimension,
                TCompatibilitySeverity::blocking,
                issue_code,
                text,
                token
            };
        }

        [[nodiscard]] static constexpr TCompatibilityIssue fatal(
            TCompatibilityDimension checked_dimension,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TCompatibilityIssue{
                checked_dimension,
                TCompatibilitySeverity::fatal,
                issue_code,
                text,
                token
            };
        }
    };
}

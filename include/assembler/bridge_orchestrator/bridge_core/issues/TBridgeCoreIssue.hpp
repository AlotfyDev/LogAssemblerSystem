#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"

/**
 * @file TBridgeCoreIssue.hpp
 * @brief Bridge Core diagnostic issue record.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - diagnostic record for bridge model declaration and advancement issues;
 * - future use in bridge registries, reports, CI validation, and trace
 *   review;
 * - independent from telemetry or logging backend.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - issue code, message, status context, blocking flag, and correlation;
 * - validity and blocking helpers;
 * - static factories for info/block/fatal-like diagnostics.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - runtime logging sink or persistent diagnostics store.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBridgeCoreIssueSeverity
    {
        none,
        info,
        warning,
        blocking,
        fatal
    };

    struct TBridgeCoreIssue final
    {
        TBridgeCoreIssueSeverity severity{TBridgeCoreIssueSeverity::none};
        TBridgeStatus bridge_status{TBridgeStatus::unknown};
        std::string_view code{};
        std::string_view message{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_present() const noexcept
        {
            return severity != TBridgeCoreIssueSeverity::none;
        }

        [[nodiscard]] constexpr bool is_blocking() const noexcept
        {
            return severity == TBridgeCoreIssueSeverity::blocking
                || severity == TBridgeCoreIssueSeverity::fatal;
        }

        [[nodiscard]] static constexpr TBridgeCoreIssue none() noexcept
        {
            return TBridgeCoreIssue{};
        }

        [[nodiscard]] static constexpr TBridgeCoreIssue info(
            TBridgeStatus status,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCoreIssue{
                TBridgeCoreIssueSeverity::info,
                status,
                issue_code,
                text,
                token
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreIssue block(
            TBridgeStatus status,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCoreIssue{
                TBridgeCoreIssueSeverity::blocking,
                status,
                issue_code,
                text,
                token
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreIssue fatal(
            TBridgeStatus status,
            std::string_view issue_code,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCoreIssue{
                TBridgeCoreIssueSeverity::fatal,
                status,
                issue_code,
                text,
                token
            };
        }
    };
}

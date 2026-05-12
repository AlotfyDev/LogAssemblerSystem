#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TObligationReport.hpp
 * @brief Bridge-visible obligation report primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - common report value for checking whether an obligation surface is present,
 *   satisfied, incomplete, unsupported, or failed;
 * - reusable reporting primitive for future compatibility checks, diagnostics,
 *   registry snapshots, tests, and bridge setup review;
 * - strict separation between obligation reporting and binding/session
 *   execution.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - obligation status enum;
 * - obligation side enum;
 * - lightweight report value with correlation token and note text;
 * - constexpr helpers for satisfied, incomplete, unsupported, and failed.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - concrete adapter-port binding execution;
 * - channel registry or binding registry ownership;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - full compatibility engine or validation framework.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This obligation foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, W03 participant descriptors, and
 * W04 channel topology where needed. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TObligationStatus
    {
        unknown,
        satisfied,
        incomplete,
        unsupported,
        failed
    };

    enum class TObligationSide
    {
        unknown,
        host_port,
        content_plugin_adapter,
        bridge,
        channel,
        binding,
        session
    };

    struct TObligationReport final
    {
        TObligationStatus status{TObligationStatus::unknown};
        TObligationSide side{TObligationSide::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view obligation_name{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_satisfied() const noexcept
        {
            return status == TObligationStatus::satisfied;
        }

        [[nodiscard]] constexpr bool is_actionable_failure() const noexcept
        {
            return status == TObligationStatus::incomplete
                || status == TObligationStatus::unsupported
                || status == TObligationStatus::failed;
        }

        [[nodiscard]] static constexpr TObligationReport satisfied(
            TObligationSide obligation_side,
            std::string_view name,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = {}) noexcept
        {
            return TObligationReport{
                TObligationStatus::satisfied,
                obligation_side,
                token,
                name,
                text
            };
        }

        [[nodiscard]] static constexpr TObligationReport incomplete(
            TObligationSide obligation_side,
            std::string_view name,
            std::string_view text = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TObligationReport{
                TObligationStatus::incomplete,
                obligation_side,
                token,
                name,
                text
            };
        }

        [[nodiscard]] static constexpr TObligationReport unsupported(
            TObligationSide obligation_side,
            std::string_view name,
            std::string_view text = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TObligationReport{
                TObligationStatus::unsupported,
                obligation_side,
                token,
                name,
                text
            };
        }

        [[nodiscard]] static constexpr TObligationReport failed(
            TObligationSide obligation_side,
            std::string_view name,
            std::string_view text = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TObligationReport{
                TObligationStatus::failed,
                obligation_side,
                token,
                name,
                text
            };
        }
    };
}
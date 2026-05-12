#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/compatibility/TBindingCompatibilityReport.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/bindings/status/TBindingStatus.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"

/**
 * @file TBindingResult.hpp
 * @brief Binding-level result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - canonical binding outcome categories independent from endpoint result
 *   systems;
 * - compatibility-aware binding result with binding id, status, bridge result,
 *   and diagnostic reason;
 * - future support for binding registries, sessions, bridge setup, and
 *   validation reports.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - binding result status enum;
 * - lightweight binding result value;
 * - accepted/rejected/deferred/failed helpers;
 * - conversion relation to W01 `TBridgeResult`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol execution or bridge orchestration;
 * - endpoint validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - session allocation or protocol execution result.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This binding model header may depend on W01 primitive carriers/results,
 * W02 protocol-state categories where needed, W03 participants, W04 channel
 * topology, and W05 obligation-surface views. It must not include endpoint
 * domain headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBindingResultStatus
    {
        accepted,
        rejected,
        deferred,
        failed
    };

    struct TBindingResult final
    {
        TBindingResultStatus status{TBindingResultStatus::failed};
        TBindingId binding_id{TBindingId::invalid()};
        TBindingStatus binding_status{TBindingStatus::unknown};
        TBindingCompatibilityReport compatibility{};
        TBridgeResult bridge_result{TBridgeResult::fail(TBridgeError::make(TBridgeErrorCode::internal_error))};
        std::string_view reason{};

        [[nodiscard]] constexpr bool accepted() const noexcept
        {
            return status == TBindingResultStatus::accepted
                && bridge_result.succeeded()
                && compatibility.is_compatible()
                && binding_id.is_valid();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TBindingResultStatus::rejected
                || bridge_result.rejected();
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TBindingResultStatus::deferred
                || bridge_result.deferred();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TBindingResultStatus::failed
                || bridge_result.failed();
        }

        [[nodiscard]] static constexpr TBindingResult accept(
            TBindingId id,
            TBindingCompatibilityReport report,
            TBindingStatus bound_status = TBindingStatus::compatible,
            std::string_view text = "binding accepted") noexcept
        {
            return TBindingResult{
                TBindingResultStatus::accepted,
                id,
                bound_status,
                report,
                report.as_bridge_result(),
                text
            };
        }

        [[nodiscard]] static constexpr TBindingResult reject(
            TBindingId id,
            TBindingCompatibilityReport report,
            std::string_view text = "binding rejected") noexcept
        {
            return TBindingResult{
                TBindingResultStatus::rejected,
                id,
                TBindingStatus::incompatible,
                report,
                report.as_bridge_result(),
                text
            };
        }

        [[nodiscard]] static constexpr TBindingResult defer(
            TBindingId id,
            TBindingCompatibilityReport report,
            std::string_view text = "binding deferred") noexcept
        {
            return TBindingResult{
                TBindingResultStatus::deferred,
                id,
                TBindingStatus::proposed,
                report,
                TBridgeResult::defer(
                    TBridgeError::make(TBridgeErrorCode::incompatible_binding, text),
                    report.correlation),
                text
            };
        }

        [[nodiscard]] static constexpr TBindingResult fail(
            TBindingId id,
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const auto report = TBindingCompatibilityReport::incompatible(text, token);

            return TBindingResult{
                TBindingResultStatus::failed,
                id,
                TBindingStatus::unknown,
                report,
                TBridgeResult::fail(
                    TBridgeError::make(TBridgeErrorCode::internal_error, text),
                    token),
                text
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingResultStatus status) noexcept
    {
        switch (status)
        {
            case TBindingResultStatus::accepted: return "accepted";
            case TBindingResultStatus::rejected: return "rejected";
            case TBindingResultStatus::deferred: return "deferred";
            case TBindingResultStatus::failed: return "failed";
        }

        return "failed";
    }
}
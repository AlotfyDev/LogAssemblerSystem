#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/bridge_carriers/results/TBridgeCarrierResult.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"

/**
 * @file TBindingCompatibilityReport.hpp
 * @brief Compatibility report for channel and obligation-surface binding.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - compatibility report across channel topology, plugin-adapter view, and
 *   port view;
 * - future support for richer diagnostics, compatibility matrices, validation
 *   gates, and bridge setup checks;
 * - report-to-result conversion without performing endpoint invocation.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - compatibility status enum;
 * - lightweight report value;
 * - static evaluator for W04 channel and W05 obligation surface pair;
 * - conversion to `TBridgeResult` for later orchestration layers.
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
 * - full validation engine or binding execution.
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
    enum class TBindingCompatibilityStatus
    {
        unknown,
        compatible,
        incompatible,
        incomplete,
        deferred
    };

    struct TBindingCompatibilityReport final
    {
        TBindingCompatibilityStatus status{TBindingCompatibilityStatus::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view reason{};
        bool channel_valid{false};
        bool channel_declared{false};
        bool surface_pair_valid{false};
        bool primary_placement_supported{false};

        [[nodiscard]] constexpr bool is_compatible() const noexcept
        {
            return status == TBindingCompatibilityStatus::compatible
                && channel_valid
                && channel_declared
                && surface_pair_valid
                && primary_placement_supported;
        }

        [[nodiscard]] constexpr TBridgeResult as_bridge_result() const noexcept
        {
            if (is_compatible())
            {
                return TBridgeResult::success(correlation);
            }

            if (status == TBindingCompatibilityStatus::deferred)
            {
                return TBridgeResult::defer(
                    TBridgeError::make(TBridgeErrorCode::incompatible_binding, reason),
                    correlation);
            }

            return TBridgeResult::reject(
                TBridgeError::make(TBridgeErrorCode::incompatible_binding, reason),
                correlation);
        }

        [[nodiscard]] static constexpr TBindingCompatibilityReport compatible(
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "binding compatible") noexcept
        {
            return TBindingCompatibilityReport{
                TBindingCompatibilityStatus::compatible,
                token,
                text,
                true,
                true,
                true,
                true
            };
        }

        [[nodiscard]] static constexpr TBindingCompatibilityReport incompatible(
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid(),
            bool is_channel_valid = false,
            bool is_channel_declared = false,
            bool is_pair_valid = false,
            bool is_primary_supported = false) noexcept
        {
            return TBindingCompatibilityReport{
                TBindingCompatibilityStatus::incompatible,
                token,
                text,
                is_channel_valid,
                is_channel_declared,
                is_pair_valid,
                is_primary_supported
            };
        }

        [[nodiscard]] static constexpr TBindingCompatibilityReport evaluate(
            const TChannel& channel,
            const TObligationSurfacePair& pair,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const bool channel_is_valid = channel.is_valid();
            const bool channel_is_declared = channel.is_declared();
            const bool pair_is_valid = pair.is_valid();
            const bool primary_supported = pair.supports_primary_placement_flow();

            if (channel_is_valid && channel_is_declared && pair_is_valid && primary_supported)
            {
                return TBindingCompatibilityReport{
                    TBindingCompatibilityStatus::compatible,
                    token,
                    "channel and obligation surfaces are compatible",
                    channel_is_valid,
                    channel_is_declared,
                    pair_is_valid,
                    primary_supported
                };
            }

            return TBindingCompatibilityReport{
                TBindingCompatibilityStatus::incompatible,
                token,
                "channel and obligation surfaces are not compatible",
                channel_is_valid,
                channel_is_declared,
                pair_is_valid,
                primary_supported
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingCompatibilityStatus status) noexcept
    {
        switch (status)
        {
            case TBindingCompatibilityStatus::unknown: return "unknown";
            case TBindingCompatibilityStatus::compatible: return "compatible";
            case TBindingCompatibilityStatus::incompatible: return "incompatible";
            case TBindingCompatibilityStatus::incomplete: return "incomplete";
            case TBindingCompatibilityStatus::deferred: return "deferred";
        }

        return "unknown";
    }
}
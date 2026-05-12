#pragma once

#include <string_view>

/**
 * @file TBridgeProtocolKind.hpp
 * @brief Bridge protocol kind taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable protocol family taxonomy for envelope placement, delivery,
 *   persistence, telemetry, ABI boundary, and diagnostic protocols;
 * - textual conversion for diagnostics and future registries;
 * - clear separation between protocol family and concrete endpoint binding.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - enum class `TBridgeProtocolKind`;
 * - classification helpers;
 * - textual conversion helper.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - concrete endpoint protocol adapter selection.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Protocol Model headers may depend on W01 carriers/results/errors,
 * W02 protocol-state foundations, W06 binding model through sessions, W07
 * compatibility through sessions, and W08 session model. They must not include
 * endpoint-domain headers such as log_level_api, write_side, read_side,
 * persistence implementations, telemetry SDKs, or thin C ABI implementation
 * internals.
 */

namespace assembler::communication_context
{
    enum class TBridgeProtocolKind
    {
        unknown,
        envelope_placement,
        registry_delivery,
        persistence_delivery,
        telemetry_export,
        abi_boundary_exchange,
        diagnostic_observation
    };

    [[nodiscard]] constexpr bool is_delivery_protocol_kind(
        TBridgeProtocolKind kind) noexcept
    {
        return kind == TBridgeProtocolKind::registry_delivery
            || kind == TBridgeProtocolKind::persistence_delivery
            || kind == TBridgeProtocolKind::telemetry_export;
    }

    [[nodiscard]] constexpr bool is_primary_exchange_protocol_kind(
        TBridgeProtocolKind kind) noexcept
    {
        return kind == TBridgeProtocolKind::envelope_placement
            || kind == TBridgeProtocolKind::registry_delivery
            || kind == TBridgeProtocolKind::persistence_delivery;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBridgeProtocolKind kind) noexcept
    {
        switch (kind)
        {
            case TBridgeProtocolKind::unknown: return "unknown";
            case TBridgeProtocolKind::envelope_placement: return "envelope_placement";
            case TBridgeProtocolKind::registry_delivery: return "registry_delivery";
            case TBridgeProtocolKind::persistence_delivery: return "persistence_delivery";
            case TBridgeProtocolKind::telemetry_export: return "telemetry_export";
            case TBridgeProtocolKind::abi_boundary_exchange: return "abi_boundary_exchange";
            case TBridgeProtocolKind::diagnostic_observation: return "diagnostic_observation";
        }

        return "unknown";
    }
}

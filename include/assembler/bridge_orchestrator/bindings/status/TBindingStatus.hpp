#pragma once

#include <string_view>

/**
 * @file TBindingStatus.hpp
 * @brief Binding lifecycle-status category model.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - canonical binding lifecycle categories;
 * - stable textual conversion for diagnostics and manifests;
 * - clear separation between binding declaration/materialization and session
 *   execution state.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - binding status enum;
 * - textual conversion helper;
 * - status readiness helpers.
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
 * - session-state machine or protocol-state transition execution.
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
    enum class TBindingStatus
    {
        unknown,
        proposed,
        incompatible,
        compatible,
        materialized,
        suspended,
        retired
    };

    [[nodiscard]] constexpr bool is_terminal(TBindingStatus status) noexcept
    {
        return status == TBindingStatus::incompatible
            || status == TBindingStatus::retired;
    }

    [[nodiscard]] constexpr bool is_usable_binding_status(TBindingStatus status) noexcept
    {
        return status == TBindingStatus::compatible
            || status == TBindingStatus::materialized;
    }

    [[nodiscard]] constexpr std::string_view to_string(TBindingStatus status) noexcept
    {
        switch (status)
        {
            case TBindingStatus::unknown: return "unknown";
            case TBindingStatus::proposed: return "proposed";
            case TBindingStatus::incompatible: return "incompatible";
            case TBindingStatus::compatible: return "compatible";
            case TBindingStatus::materialized: return "materialized";
            case TBindingStatus::suspended: return "suspended";
            case TBindingStatus::retired: return "retired";
        }

        return "unknown";
    }
}
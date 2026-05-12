#pragma once

#include <string_view>

/**
 * @file TDiagnosticCategory.hpp
 * @brief Diagnostic category taxonomy for optional ASCC diagnostics.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable category vocabulary for model, registry, bridge, protocol,
 *   session, binding, channel, concrete binding, and integration diagnostics;
 * - no endpoint-private diagnostic categories;
 * - string conversion for local diagnostic reports.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - enum class `TDiagnosticCategory`;
 * - public category helper;
 * - textual conversion.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - telemetry exporters;
 * - logging framework integration;
 * - persistence, database, file IO, or network IO;
 * - runtime scheduling, service locator, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - ownership or mutation of diagnosed objects;
 * - replacement of Bridge, Protocol, Session, Binding, Channel, Registry, or
 *   concrete binding semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W12 may depend on W01-W11 public Communication Context surfaces.
 * It must remain optional and diagnostic-only. It must not be required by W14
 * concrete bindings or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    enum class TDiagnosticCategory
    {
        unknown,
        carrier,
        channel,
        binding,
        compatibility,
        session,
        protocol,
        bridge_core,
        registry,
        concrete_binding,
        integration_skeleton,
        policy,
        boundary
    };

    [[nodiscard]] constexpr bool is_core_model_diagnostic_category(
        TDiagnosticCategory category) noexcept
    {
        return category == TDiagnosticCategory::carrier
            || category == TDiagnosticCategory::channel
            || category == TDiagnosticCategory::binding
            || category == TDiagnosticCategory::compatibility
            || category == TDiagnosticCategory::session
            || category == TDiagnosticCategory::protocol
            || category == TDiagnosticCategory::bridge_core;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TDiagnosticCategory category) noexcept
    {
        switch (category)
        {
            case TDiagnosticCategory::unknown: return "unknown";
            case TDiagnosticCategory::carrier: return "carrier";
            case TDiagnosticCategory::channel: return "channel";
            case TDiagnosticCategory::binding: return "binding";
            case TDiagnosticCategory::compatibility: return "compatibility";
            case TDiagnosticCategory::session: return "session";
            case TDiagnosticCategory::protocol: return "protocol";
            case TDiagnosticCategory::bridge_core: return "bridge_core";
            case TDiagnosticCategory::registry: return "registry";
            case TDiagnosticCategory::concrete_binding: return "concrete_binding";
            case TDiagnosticCategory::integration_skeleton: return "integration_skeleton";
            case TDiagnosticCategory::policy: return "policy";
            case TDiagnosticCategory::boundary: return "boundary";
        }

        return "unknown";
    }
}

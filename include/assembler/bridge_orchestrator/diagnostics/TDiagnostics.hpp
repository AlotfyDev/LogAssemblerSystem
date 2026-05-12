#pragma once

#include "assembler/communication_context/registries/TOptionalRegistries.hpp"
#include "assembler/communication_context/diagnostics/builders/TBridgeDiagnosticBuilder.hpp"
#include "assembler/communication_context/diagnostics/builders/TRegistryDiagnosticBuilder.hpp"
#include "assembler/communication_context/diagnostics/categories/TDiagnosticCategory.hpp"
#include "assembler/communication_context/diagnostics/collectors/TDiagnosticCollector.hpp"
#include "assembler/communication_context/diagnostics/ids/TDiagnosticId.hpp"
#include "assembler/communication_context/diagnostics/policies/TDiagnosticPolicy.hpp"
#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"
#include "assembler/communication_context/diagnostics/reports/TDiagnosticReport.hpp"
#include "assembler/communication_context/diagnostics/severity/TDiagnosticSeverity.hpp"
#include "assembler/communication_context/diagnostics/snapshots/TDiagnosticSnapshot.hpp"
#include "assembler/communication_context/diagnostics/views/TDiagnosticView.hpp"

/**
 * @file TDiagnostics.hpp
 * @brief Aggregate include for W12 optional diagnostics.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - single aggregate include for the optional diagnostics layer;
 * - stable availability marker for downstream diagnostics-aware waves and
 *   smoke tests;
 * - explicit diagnostic optionality without telemetry or persistence mandate.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - aggregate include only;
 * - availability marker;
 * - no additional runtime behavior.
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
    inline constexpr bool ASCC_W12_DIAGNOSTICS_AVAILABLE = true;
}

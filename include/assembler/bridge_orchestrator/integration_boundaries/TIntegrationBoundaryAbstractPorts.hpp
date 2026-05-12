#pragma once

#include "assembler/communication_context/diagnostics/TDiagnostics.hpp"
#include "assembler/communication_context/integration_boundaries/capabilities/TIntegrationBoundaryCapability.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffHandle.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"
#include "assembler/communication_context/integration_boundaries/directions/TIntegrationBoundaryDirection.hpp"
#include "assembler/communication_context/integration_boundaries/kinds/TIntegrationBoundaryKind.hpp"
#include "assembler/communication_context/integration_boundaries/policies/TIntegrationBoundaryPolicy.hpp"
#include "assembler/communication_context/integration_boundaries/ports/TIntegrationBoundaryPort.hpp"
#include "assembler/communication_context/integration_boundaries/reports/TIntegrationBoundaryReport.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"
#include "assembler/communication_context/integration_boundaries/statuses/TBoundaryHandoffStatus.hpp"
#include "assembler/communication_context/integration_boundaries/traits/TIntegrationBoundaryPortTraits.hpp"
#include "assembler/communication_context/integration_boundaries/views/TIntegrationBoundaryPortView.hpp"

/**
 * @file TIntegrationBoundaryAbstractPorts.hpp
 * @brief Aggregate include for W13 future-facing abstract integration boundary ports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - single aggregate include for W13 abstract boundary surfaces;
 * - stable availability marker for future boundary-oriented waves;
 * - optional, future-facing abstraction without concrete endpoints.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - aggregate include only;
 * - availability marker;
 * - no runtime behavior.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete persistence, telemetry, ABI, read-side, or external receiver
 *   integration;
 * - endpoint-domain internals;
 * - adapter/port call wiring for concrete endpoints;
 * - storage, database, file IO, network IO, telemetry export, or logging sinks;
 * - runtime scheduling, service location, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - bridge execution replacement;
 * - ownership over downstream lifecycle or endpoint resources.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W13 may depend on W01-W12 public Communication Context surfaces.
 * It must remain future-facing and abstract. Concrete implementations belong
 * to later dedicated binding waves.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_W13_INTEGRATION_BOUNDARY_ABSTRACT_PORTS_AVAILABLE = true;
}

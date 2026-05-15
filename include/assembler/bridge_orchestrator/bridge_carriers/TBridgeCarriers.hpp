#pragma once

/**
 * @file TBridgeCarriers.hpp
 * @brief Canonical operational composition surface for the ASCC bridge carriers subsystem.
 *
 * This file is NOT a convenience umbrella include.
 *
 * This file defines the stable operational boundary exported by the
 * bridge_carriers subsystem.
 *
 * The goal is to provide:
 *
 * - a canonical subsystem entry surface
 * - a stable dependency boundary
 * - bounded operational exports
 * - controlled runtime composition topology
 *
 * This prevents higher-level subsystems from depending directly on internal
 * runtime topology or unstable implementation details.
 *
 * Higher-level domains expected to consume this surface:
 *
 * - protocols/
 * - sessions/
 * - participants/
 * - obligations/
 * - diagnostics/
 * - facade_layer/
 * - pipeline composition/orchestration layers
 *
 * Export policy:
 *
 * This surface exports ONLY:
 *
 * - stable operational contracts
 * - runtime orchestration primitives
 * - readiness/runtime evidence surfaces
 * - semantic compatibility/binding layers
 * - bounded carrier runtime semantics
 *
 * This surface intentionally does NOT export:
 *
 * - low-level helpers
 * - unstable implementation details
 * - temporary runtime adapters
 * - experimental carrier internals
 *
 * Architectural role:
 *
 * bridge_carriers/ is no longer a descriptive contract collection.
 *
 * It is now an operational subsystem responsible for:
 *
 * - carrier runtime validation
 * - requirement satisfaction
 * - runtime flow orchestration
 * - readiness projection
 * - protocol compatibility semantics
 * - obligation semantic resolution
 *
 * This file therefore acts as the canonical operational composition surface
 * for all carrier runtime semantics inside the ASCC communication context.
 */

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"

#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationEngine.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"

#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionEngine.hpp"
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"

#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRuntime.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowReport.hpp"

#include "assembler/communication_context/bridge_carriers/readiness/TCarrierReadinessReport.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TCarrierRuntimeReadinessView.hpp"

#include "assembler/communication_context/bridge_carriers/protocols/TCarrierProtocolBindingMap.hpp"

#include "assembler/communication_context/bridge_carriers/obligations/TCarrierObligationResolver.hpp"

#pragma once

#include "assembler/communication_context/bridge_core/TBridgeCore.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/TFirstIntegrationSkeleton.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/config/TFirstIntegrationSkeletonConfig.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/factory/TFirstIntegrationSkeletonFactory.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/ids/TFirstIntegrationSkeletonIdSet.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/plans/TFirstIntegrationSkeletonModelPlan.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/reports/TFirstIntegrationSkeletonReport.hpp"

/**
 * @file TFirstIntegrationSkeletonBinding.hpp
 * @brief Aggregate include for W15 first integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - single include surface for W15;
 * - stable include for downstream integration tests and future waves;
 * - explicit availability marker.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - aggregate includes only;
 * - availability marker;
 * - no additional runtime behavior.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete endpoint-domain internals;
 * - Write Side slot/container/round implementation;
 * - Log Level API envelope assembly, validation, metadata, or timestamp internals;
 * - runtime scheduling, threading, async execution, persistence, telemetry, ABI, or database behavior;
 * - replacing W09 protocol model or W10 bridge model-step orchestration;
 * - hiding bridge-visible failure/report states.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W15 may depend on W01-W10, W14A, and W14B public include surfaces.
 * It must not include concrete endpoint-domain headers such as
 * `assembler/log_level_api/...` or `assembler/write_side/...` internals.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_W15_FIRST_INTEGRATION_SKELETON_AVAILABLE = true;
}

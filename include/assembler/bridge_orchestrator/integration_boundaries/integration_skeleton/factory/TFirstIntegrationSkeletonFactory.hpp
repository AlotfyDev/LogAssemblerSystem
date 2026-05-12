#pragma once

#include "assembler/communication_context/integration_boundaries/integration_skeleton/TFirstIntegrationSkeleton.hpp"

/**
 * @file TFirstIntegrationSkeletonFactory.hpp
 * @brief Factory helpers for the first ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - stable construction helpers for the first integration skeleton;
 * - future extension point for explicit W14A/W14B configuration handoff;
 * - no dynamic allocation or runtime service locator.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - default construction;
 * - construction from config;
 * - construction from config and correlation token.
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
    struct TFirstIntegrationSkeletonFactory final
    {
        [[nodiscard]] static constexpr TFirstIntegrationSkeleton make_default() noexcept
        {
            return TFirstIntegrationSkeleton{};
        }

        [[nodiscard]] static constexpr TFirstIntegrationSkeleton from_config(
            TFirstIntegrationSkeletonConfig config) noexcept
        {
            return TFirstIntegrationSkeleton(config);
        }

        [[nodiscard]] static constexpr TFirstIntegrationSkeleton from_config_and_token(
            TFirstIntegrationSkeletonConfig config,
            TCorrelationToken token) noexcept
        {
            return TFirstIntegrationSkeleton(config, token);
        }
    };
}

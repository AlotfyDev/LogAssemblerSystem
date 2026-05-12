#pragma once

#include <string_view>

/**
 * @file TCompatibilityDimension.hpp
 * @brief Compatibility dimension taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable compatibility dimensions for channel, participant, surface,
 *   binding, policy, lifecycle, direction, and future protocol checks;
 * - textual conversion suitable for diagnostics, manifests, and validation
 *   reports;
 * - compatibility categories that remain independent from endpoint internals.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - enum class `TCompatibilityDimension`;
 * - constexpr `to_string` conversion;
 * - basic classification helper for structural dimensions.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol stepping or bridge orchestration;
 * - endpoint-domain validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - concrete endpoint-specific compatibility dimensions.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Compatibility model headers may depend on W01 carriers/results, W03
 * participant views, W04 channel topology, W05 obligation-surface views, and
 * W06 binding model declarations. They must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TCompatibilityDimension
    {
        unknown,
        channel_topology,
        participant_roles,
        obligation_surfaces,
        placement_flow,
        binding_profile,
        binding_status,
        lifecycle_readiness,
        protocol_readiness,
        policy_alignment,
        authority_boundary
    };

    [[nodiscard]] constexpr bool is_structural_dimension(
        TCompatibilityDimension dimension) noexcept
    {
        return dimension == TCompatibilityDimension::channel_topology
            || dimension == TCompatibilityDimension::participant_roles
            || dimension == TCompatibilityDimension::obligation_surfaces
            || dimension == TCompatibilityDimension::placement_flow
            || dimension == TCompatibilityDimension::binding_profile;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TCompatibilityDimension dimension) noexcept
    {
        switch (dimension)
        {
            case TCompatibilityDimension::unknown: return "unknown";
            case TCompatibilityDimension::channel_topology: return "channel_topology";
            case TCompatibilityDimension::participant_roles: return "participant_roles";
            case TCompatibilityDimension::obligation_surfaces: return "obligation_surfaces";
            case TCompatibilityDimension::placement_flow: return "placement_flow";
            case TCompatibilityDimension::binding_profile: return "binding_profile";
            case TCompatibilityDimension::binding_status: return "binding_status";
            case TCompatibilityDimension::lifecycle_readiness: return "lifecycle_readiness";
            case TCompatibilityDimension::protocol_readiness: return "protocol_readiness";
            case TCompatibilityDimension::policy_alignment: return "policy_alignment";
            case TCompatibilityDimension::authority_boundary: return "authority_boundary";
        }

        return "unknown";
    }
}

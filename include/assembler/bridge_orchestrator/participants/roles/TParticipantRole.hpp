#pragma once

#include <string_view>

/**
 * @file TParticipantRole.hpp
 * @brief Bridge-visible participant-role vocabulary.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative participant/role foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical role vocabulary for communication participants;
 * - clear distinction between content-provider, host-provider, receiver,
 *   boundary, observer, registry, telemetry, and ABI-facing roles;
 * - stable role names usable by channels, bindings, sessions, compatibility,
 *   registries, diagnostics, and bridge protocols.
 *
 * @section ascc_current_wave Current W03 Implementation Scope
 * This W03 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable participant roles,
 * participant descriptors, participant views, and bridge-visible identity
 * surfaces without endpoint-domain dependency.
 *
 * - participant-role enum;
 * - role classification helpers;
 * - constexpr role-name projection;
 * - no endpoint ownership or endpoint implementation exposure.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - endpoint lifecycle state;
 * - adapter or port obligations;
 * - channel, binding, session, or registry ownership;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This participant foundation header may depend on W01 primitive carriers and,
 * where needed, W02 protocol-state concepts. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TParticipantRole
    {
        unknown,

        content_provider,
        host_provider,
        receiver_provider,

        registry_provider,
        persistence_provider,
        telemetry_provider,
        abi_boundary_provider,

        diagnostic_observer,
        bridge_orchestrator,
        governance_provider
    };

    [[nodiscard]] constexpr bool is_provider_role(TParticipantRole role) noexcept
    {
        return role == TParticipantRole::content_provider
            || role == TParticipantRole::host_provider
            || role == TParticipantRole::receiver_provider
            || role == TParticipantRole::registry_provider
            || role == TParticipantRole::persistence_provider
            || role == TParticipantRole::telemetry_provider
            || role == TParticipantRole::abi_boundary_provider
            || role == TParticipantRole::governance_provider;
    }

    [[nodiscard]] constexpr bool is_boundary_role(TParticipantRole role) noexcept
    {
        return role == TParticipantRole::receiver_provider
            || role == TParticipantRole::registry_provider
            || role == TParticipantRole::persistence_provider
            || role == TParticipantRole::telemetry_provider
            || role == TParticipantRole::abi_boundary_provider;
    }

    [[nodiscard]] constexpr bool is_observer_role(TParticipantRole role) noexcept
    {
        return role == TParticipantRole::diagnostic_observer;
    }

    [[nodiscard]] constexpr bool participates_in_primary_exchange(TParticipantRole role) noexcept
    {
        return role == TParticipantRole::content_provider
            || role == TParticipantRole::host_provider
            || role == TParticipantRole::receiver_provider;
    }

    [[nodiscard]] constexpr std::string_view to_string(TParticipantRole role) noexcept
    {
        switch (role)
        {
            case TParticipantRole::unknown: return "unknown";
            case TParticipantRole::content_provider: return "content_provider";
            case TParticipantRole::host_provider: return "host_provider";
            case TParticipantRole::receiver_provider: return "receiver_provider";
            case TParticipantRole::registry_provider: return "registry_provider";
            case TParticipantRole::persistence_provider: return "persistence_provider";
            case TParticipantRole::telemetry_provider: return "telemetry_provider";
            case TParticipantRole::abi_boundary_provider: return "abi_boundary_provider";
            case TParticipantRole::diagnostic_observer: return "diagnostic_observer";
            case TParticipantRole::bridge_orchestrator: return "bridge_orchestrator";
            case TParticipantRole::governance_provider: return "governance_provider";
        }

        return "unknown";
    }
}
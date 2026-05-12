#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"

/**
 * @file TParticipant.hpp
 * @brief Bridge-visible participant descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative participant/role foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical participant descriptor for endpoint-facing communication actors
 *   without exposing endpoint internals;
 * - stable participant identity usable by channel topology, adapter-port
 *   binding, session lifecycle, compatibility checks, registries, diagnostics,
 *   and protocol snapshots;
 * - future support for multiple participant identity families while preserving
 *   opaque, bridge-visible semantics.
 *
 * @section ascc_current_wave Current W03 Implementation Scope
 * This W03 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable participant roles,
 * participant descriptors, participant views, and bridge-visible identity
 * surfaces without endpoint-domain dependency.
 *
 * - opaque participant id;
 * - participant role;
 * - stable domain/family labels;
 * - correlation token for context-aware construction;
 * - validity and role classification helpers.
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
 * - concrete endpoint object references or endpoint private state.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This participant foundation header may depend on W01 primitive carriers and,
 * where needed, W02 protocol-state concepts. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TParticipant final
    {
        std::uint64_t participant_id{0};
        TParticipantRole role{TParticipantRole::unknown};
        std::string_view domain{};
        std::string_view family{};
        std::string_view display_name{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return participant_id != 0u
                && role != TParticipantRole::unknown
                && !domain.empty();
        }

        [[nodiscard]] constexpr bool is_provider() const noexcept
        {
            return is_provider_role(role);
        }

        [[nodiscard]] constexpr bool is_boundary() const noexcept
        {
            return is_boundary_role(role);
        }

        [[nodiscard]] constexpr bool is_observer() const noexcept
        {
            return is_observer_role(role);
        }

        [[nodiscard]] constexpr bool participates_in_exchange() const noexcept
        {
            return participates_in_primary_exchange(role);
        }

        [[nodiscard]] static constexpr TParticipant invalid() noexcept
        {
            return TParticipant{};
        }

        [[nodiscard]] static constexpr TParticipant make(
            std::uint64_t id,
            TParticipantRole participant_role,
            std::string_view domain_name,
            std::string_view participant_family = {},
            std::string_view participant_display_name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipant{
                id,
                participant_role,
                domain_name,
                participant_family,
                participant_display_name,
                token
            };
        }

        friend constexpr bool operator==(
            const TParticipant& lhs,
            const TParticipant& rhs) noexcept
        {
            return lhs.participant_id == rhs.participant_id
                && lhs.role == rhs.role
                && lhs.domain == rhs.domain;
        }

        friend constexpr bool operator!=(
            const TParticipant& lhs,
            const TParticipant& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
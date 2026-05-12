#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"

/**
 * @file TParticipantView.hpp
 * @brief Read-only bridge-visible participant view.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative participant/role foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - safe read-only projection of a participant descriptor;
 * - diagnostic and validation-friendly participant surface for channels,
 *   bindings, sessions, registries, compatibility, and protocol reports;
 * - future extension point for participant capability projection without
 *   exposing endpoint internals or concrete domain objects.
 *
 * @section ascc_current_wave Current W03 Implementation Scope
 * This W03 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable participant roles,
 * participant descriptors, participant views, and bridge-visible identity
 * surfaces without endpoint-domain dependency.
 *
 * - participant id;
 * - participant role;
 * - domain/family/display labels;
 * - correlation token;
 * - validity and classification helpers;
 * - construction from TParticipant.
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
 * - mutable participant lifecycle or endpoint-owned state.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This participant foundation header may depend on W01 primitive carriers and,
 * where needed, W02 protocol-state concepts. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TParticipantView final
    {
        std::uint64_t participant_id{0};
        TParticipantRole role{TParticipantRole::unknown};
        std::string_view domain{};
        std::string_view family{};
        std::string_view display_name{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        bool valid{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return valid
                && participant_id != 0u
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

        [[nodiscard]] constexpr bool participates_in_exchange() const noexcept
        {
            return participates_in_primary_exchange(role);
        }

        [[nodiscard]] static constexpr TParticipantView from_participant(
            const TParticipant& participant) noexcept
        {
            return TParticipantView{
                participant.participant_id,
                participant.role,
                participant.domain,
                participant.family,
                participant.display_name,
                participant.correlation,
                participant.is_valid()
            };
        }

        [[nodiscard]] static constexpr TParticipantView invalid() noexcept
        {
            return TParticipantView{};
        }
    };
}
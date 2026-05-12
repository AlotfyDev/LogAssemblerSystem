#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"
#include "assembler/communication_context/channels/profiles/TChannelProfile.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"

/**
 * @file TChannel.hpp
 * @brief Bridge-visible channel topology descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative channel-foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical channel topology object connecting bridge-visible participants
 *   under a declared profile and binding policy;
 * - stable topology input for later binding, compatibility, session, protocol,
 *   registry, diagnostics, and bridge orchestration layers;
 * - future support for richer participant sets without becoming a session,
 *   binding, broker, queue, or endpoint implementation.
 *
 * @section ascc_current_wave Current W04 Implementation Scope
 * This W04 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable channel profile,
 * channel binding policy, and channel topology values without session
 * execution, binding execution, bridge orchestration, or endpoint-domain
 * dependency.
 *
 * - opaque channel id;
 * - source and target participant descriptors;
 * - channel profile;
 * - channel binding policy;
 * - channel status and correlation token;
 * - validity and role-compatibility helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - adapter or port obligation implementation;
 * - concrete adapter-port binding execution;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - runtime message routing or session exchange execution.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This channel foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, and W03 participant descriptors.
 * It must not include endpoint-domain headers such as log_level_api, write_side,
 * read_side, persistence implementations, telemetry SDKs, or thin C ABI
 * implementation internals.
 */

namespace assembler::communication_context
{
    enum class TChannelStatus
    {
        unknown,
        declared,
        active,
        suspended,
        retired
    };

    struct TChannel final
    {
        std::uint64_t channel_id{0};
        TParticipant source{TParticipant::invalid()};
        TParticipant target{TParticipant::invalid()};
        TChannelProfile profile{};
        TChannelBindingPolicy binding_policy{};
        TChannelStatus status{TChannelStatus::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view channel_name{};

        [[nodiscard]] constexpr bool has_valid_identity() const noexcept
        {
            return channel_id != 0u;
        }

        [[nodiscard]] constexpr bool has_valid_participants() const noexcept
        {
            return source.is_valid()
                && target.is_valid()
                && source.participant_id != target.participant_id;
        }

        [[nodiscard]] constexpr bool has_compatible_roles() const noexcept
        {
            if (!has_valid_participants())
            {
                return false;
            }

            if (profile.direction == TChannelDirection::observer_only)
            {
                return target.role == TParticipantRole::diagnostic_observer;
            }

            return source.role == TParticipantRole::content_provider
                && (target.role == TParticipantRole::host_provider
                    || target.role == TParticipantRole::receiver_provider
                    || target.role == TParticipantRole::registry_provider
                    || target.role == TParticipantRole::persistence_provider
                    || target.role == TParticipantRole::telemetry_provider
                    || target.role == TParticipantRole::abi_boundary_provider);
        }

        [[nodiscard]] constexpr bool is_declared() const noexcept
        {
            return status == TChannelStatus::declared
                || status == TChannelStatus::active;
        }

        [[nodiscard]] constexpr bool is_active() const noexcept
        {
            return status == TChannelStatus::active;
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return has_valid_identity()
                && has_valid_participants()
                && profile.is_valid()
                && binding_policy.is_valid()
                && binding_policy.is_compatible_with(profile)
                && (!binding_policy.require_compatible_roles || has_compatible_roles())
                && status != TChannelStatus::unknown;
        }

        [[nodiscard]] constexpr TParticipantView source_view() const noexcept
        {
            return TParticipantView::from_participant(source);
        }

        [[nodiscard]] constexpr TParticipantView target_view() const noexcept
        {
            return TParticipantView::from_participant(target);
        }

        [[nodiscard]] static constexpr TChannel declare(
            std::uint64_t id,
            TParticipant source_participant,
            TParticipant target_participant,
            TChannelProfile channel_profile,
            TChannelBindingPolicy policy,
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TChannel{
                id,
                source_participant,
                target_participant,
                channel_profile,
                policy,
                TChannelStatus::declared,
                token,
                name
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(TChannelStatus status) noexcept
    {
        switch (status)
        {
            case TChannelStatus::unknown: return "unknown";
            case TChannelStatus::declared: return "declared";
            case TChannelStatus::active: return "active";
            case TChannelStatus::suspended: return "suspended";
            case TChannelStatus::retired: return "retired";
        }

        return "unknown";
    }
}
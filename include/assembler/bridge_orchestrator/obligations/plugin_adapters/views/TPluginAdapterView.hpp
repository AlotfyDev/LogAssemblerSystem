#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationProfile.hpp"

/**
 * @file TPluginAdapterView.hpp
 * @brief Read-only bridge-visible content-side plugin-adapter view.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - diagnostic and binding-preflight projection for a content-side plugin
 *   adapter;
 * - future support for registries, compatibility matrices, bridge setup,
 *   protocol snapshots, and channel diagnostics;
 * - read-only projection that exposes obligation identity without exposing
 *   endpoint internals or payload internals.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - opaque adapter id;
 * - participant view;
 * - plugin-adapter obligation profile;
 * - correlation token;
 * - validity and primary-placement support helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - concrete adapter-port binding execution;
 * - channel registry or binding registry ownership;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - concrete plugin adapter object ownership.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This obligation foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, W03 participant descriptors, and
 * W04 channel topology where needed. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TPluginAdapterView final
    {
        std::uint64_t adapter_id{0};
        TParticipantView participant{};
        TPluginAdapterObligationProfile obligation_profile{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view display_name{};
        bool valid{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return valid
                && adapter_id != 0u
                && participant.is_valid()
                && obligation_profile.is_valid();
        }

        [[nodiscard]] constexpr bool supports_primary_placement_flow() const noexcept
        {
            return is_valid()
                && obligation_profile.supports_primary_placement_flow();
        }

        [[nodiscard]] static constexpr TPluginAdapterView make(
            std::uint64_t id,
            TParticipantView participant_view,
            TPluginAdapterObligationProfile profile,
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPluginAdapterView{
                id,
                participant_view,
                profile,
                token,
                name,
                id != 0u && participant_view.is_valid() && profile.is_valid()
            };
        }

        [[nodiscard]] static constexpr TPluginAdapterView invalid() noexcept
        {
            return TPluginAdapterView{};
        }
    };
}
#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/compatibility/TBindingCompatibilityReport.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/bindings/profiles/TBindingProfile.hpp"
#include "assembler/communication_context/bindings/status/TBindingStatus.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"

/**
 * @file TBindingView.hpp
 * @brief Read-only binding projection.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - read-only bridge-visible projection for a binding;
 * - future diagnostic view for registries, sessions, bridge snapshots,
 *   protocol traces, and compatibility reporting;
 * - stable public view that exposes binding metadata without exposing endpoint
 *   internals or session execution.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - binding id;
 * - channel id;
 * - plugin-adapter and port views;
 * - binding profile, compatibility report, status, correlation, and name;
 * - validity and usability helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol execution or bridge orchestration;
 * - endpoint validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - mutable binding registry entry or endpoint object ownership.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This binding model header may depend on W01 primitive carriers/results,
 * W02 protocol-state categories where needed, W03 participants, W04 channel
 * topology, and W05 obligation-surface views. It must not include endpoint
 * domain headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBindingView final
    {
        TBindingId binding_id{TBindingId::invalid()};
        std::uint64_t channel_id{0};
        TPluginAdapterView plugin_adapter{};
        TPortView port{};
        TBindingProfile profile{};
        TBindingCompatibilityReport compatibility{};
        TBindingStatus status{TBindingStatus::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return binding_id.is_valid()
                && channel_id != 0u
                && plugin_adapter.is_valid()
                && port.is_valid()
                && profile.is_valid()
                && compatibility.is_compatible()
                && status != TBindingStatus::unknown;
        }

        [[nodiscard]] constexpr bool is_usable() const noexcept
        {
            return is_valid() && is_usable_binding_status(status);
        }

        [[nodiscard]] static constexpr TBindingView invalid() noexcept
        {
            return TBindingView{};
        }
    };
}
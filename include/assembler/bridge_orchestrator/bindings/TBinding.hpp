#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/compatibility/TBindingCompatibilityReport.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/bindings/profiles/TBindingProfile.hpp"
#include "assembler/communication_context/bindings/results/TBindingResult.hpp"
#include "assembler/communication_context/bindings/status/TBindingStatus.hpp"
#include "assembler/communication_context/bindings/binding_views/TBindingView.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"

/**
 * @file TBinding.hpp
 * @brief Binding declaration between channel topology and obligation surfaces.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - canonical binding model joining a channel, content-side plugin adapter
 *   surface, and host-side port surface;
 * - future source for session materialization, bridge setup, compatibility
 *   registries, diagnostics, and protocol bootstrap;
 * - strict separation between binding declaration and session/protocol
 *   execution.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - binding value object;
 * - proposal, compatibility evaluation, materialization-status helper, view,
 *   and result helpers;
 * - no endpoint invocation and no session allocation.
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
 * - binding registry, session factory, protocol runner, or bridge executor.
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
    struct TBinding final
    {
        TBindingId binding_id{TBindingId::invalid()};
        TChannel channel{};
        TObligationSurfacePair surface_pair{};
        TBindingProfile profile{};
        TBindingCompatibilityReport compatibility{};
        TBindingStatus status{TBindingStatus::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view binding_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return binding_id.is_valid()
                && channel.is_valid()
                && surface_pair.is_valid()
                && profile.is_valid()
                && status != TBindingStatus::unknown;
        }

        [[nodiscard]] constexpr bool is_compatible() const noexcept
        {
            return is_valid()
                && compatibility.is_compatible()
                && (status == TBindingStatus::compatible
                    || status == TBindingStatus::materialized);
        }

        [[nodiscard]] constexpr bool is_materialized() const noexcept
        {
            return is_valid()
                && status == TBindingStatus::materialized
                && compatibility.is_compatible();
        }

        [[nodiscard]] constexpr bool may_materialize_session() const noexcept
        {
            return is_compatible()
                && profile.allow_session_materialization;
        }

        [[nodiscard]] constexpr TBindingView view() const noexcept
        {
            if (!is_valid())
            {
                return TBindingView::invalid();
            }

            return TBindingView{
                binding_id,
                channel.channel_id,
                surface_pair.plugin_adapter,
                surface_pair.port,
                profile,
                compatibility,
                status,
                correlation,
                binding_name
            };
        }

        [[nodiscard]] constexpr TBindingResult result() const noexcept
        {
            if (is_compatible())
            {
                return TBindingResult::accept(binding_id, compatibility, status);
            }

            return TBindingResult::reject(binding_id, compatibility);
        }

        [[nodiscard]] static constexpr TBinding propose(
            TBindingId id,
            TChannel declared_channel,
            TObligationSurfacePair pair,
            TBindingProfile binding_profile = TBindingProfile::strict_static_one_to_one(),
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const auto report = TBindingCompatibilityReport::evaluate(
                declared_channel,
                pair,
                token);

            const auto proposed_status = report.is_compatible()
                ? TBindingStatus::compatible
                : TBindingStatus::incompatible;

            return TBinding{
                id,
                declared_channel,
                pair,
                binding_profile,
                report,
                proposed_status,
                token,
                name
            };
        }

        [[nodiscard]] static constexpr TBinding materialize_declaration_only(
            TBinding compatible_binding) noexcept
        {
            if (!compatible_binding.is_compatible())
            {
                return compatible_binding;
            }

            compatible_binding.status = TBindingStatus::materialized;
            return compatible_binding;
        }
    };
}
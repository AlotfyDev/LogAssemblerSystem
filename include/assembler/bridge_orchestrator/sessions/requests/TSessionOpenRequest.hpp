#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/compatibility/TCompatibilityEvaluator.hpp"
#include "assembler/communication_context/compatibility/views/TCompatibilityView.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"

/**
 * @file TSessionOpenRequest.hpp
 * @brief Session-opening request carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - bridge-visible request to open a session from an already declared
 *   binding;
 * - compatibility snapshot capture before session construction;
 * - future support for registries, channel/session indexes, and bridge setup
 *   workflows without endpoint-domain coupling.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - session id, binding, policy, compatibility view, correlation, and name;
 * - eligibility helpers for declaration-only or materialized-binding session
 *   opening;
 * - static factory that evaluates strict compatibility using W07.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - endpoint resource acquisition or session registry insertion.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TSessionOpenRequest final
    {
        TSessionId session_id{TSessionId::invalid()};
        TBinding binding{};
        TSessionPolicy policy{};
        TCompatibilityView compatibility{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view session_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return session_id.is_valid()
                && binding.is_valid()
                && policy.is_valid()
                && compatibility.binding.is_valid();
        }

        [[nodiscard]] constexpr bool is_openable() const noexcept
        {
            if (!is_valid() || !compatibility.passed())
            {
                return false;
            }

            if (policy.require_strict_compatibility
                && !binding.is_compatible())
            {
                return false;
            }

            if (policy.requires_materialized_binding())
            {
                return binding.is_materialized();
            }

            return policy.allows_open_from_compatible_binding()
                && binding.is_compatible();
        }

        [[nodiscard]] static constexpr TSessionOpenRequest make(
            TSessionId id,
            TBinding declared_binding,
            TSessionPolicy session_policy = TSessionPolicy::strict_declaration_session(),
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const auto view = TCompatibilityEvaluator::view_strict_binding(declared_binding);

            return TSessionOpenRequest{
                id,
                declared_binding,
                session_policy,
                view,
                token,
                name
            };
        }
    };
}

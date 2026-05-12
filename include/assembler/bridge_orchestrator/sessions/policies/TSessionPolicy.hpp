#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TSessionPolicy.hpp
 * @brief Session-opening policy descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - declarative policy governing when a compatible binding may become a
 *   session;
 * - future extension point for expiration, retries, capacity, strict
 *   compatibility, protocol-readiness, and lifecycle gates;
 * - explicit separation from binding profile and endpoint policy.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - policy flags for strict compatibility and declaration-only opening;
 * - lightweight retry/step limits;
 * - static policy factories for strict declaration sessions.
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
 * - endpoint policy execution or runtime scheduler ownership.
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
    struct TSessionPolicy final
    {
        bool require_strict_compatibility{true};
        bool allow_declaration_only_open{true};
        bool require_binding_materialized{false};
        bool allow_suspend{false};
        bool allow_reopen{false};
        bool allow_protocol_bootstrap{false};
        std::uint32_t max_protocol_steps{0u};
        std::uint32_t policy_version{1u};
        std::string_view policy_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return policy_version > 0u;
        }

        [[nodiscard]] constexpr bool allows_open_from_compatible_binding() const noexcept
        {
            return is_valid()
                && allow_declaration_only_open
                && !require_binding_materialized;
        }

        [[nodiscard]] constexpr bool requires_materialized_binding() const noexcept
        {
            return is_valid() && require_binding_materialized;
        }

        [[nodiscard]] static constexpr TSessionPolicy strict_declaration_session(
            std::string_view name = "strict_declaration_session_policy") noexcept
        {
            return TSessionPolicy{
                true,
                true,
                false,
                false,
                false,
                false,
                0u,
                1u,
                name
            };
        }

        [[nodiscard]] static constexpr TSessionPolicy materialized_binding_session(
            std::string_view name = "materialized_binding_session_policy") noexcept
        {
            return TSessionPolicy{
                true,
                false,
                true,
                false,
                false,
                false,
                0u,
                1u,
                name
            };
        }
    };
}

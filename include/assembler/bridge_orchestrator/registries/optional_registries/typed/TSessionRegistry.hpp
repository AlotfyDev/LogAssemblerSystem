#pragma once

#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"

/**
 * @file TSessionRegistry.hpp
 * @brief Optional bounded registry for session declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - typed registry over `TSessionId` and `TSession`;
 * - diagnostic grouping of sessions without owning endpoint resources;
 * - no protocol execution authority.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - register/find/contains/snapshot helpers;
 * - bounded fixed-capacity storage via `TBoundedRegistry`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - mandatory runtime ownership;
 * - service locator behavior;
 * - dependency injection container behavior;
 * - scheduler, broker, queue, worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - persistence, database, telemetry, ABI, or downstream registry behavior;
 * - mutation of endpoint-owned resources;
 * - replacement of Channel, Binding, Session, Protocol, or Bridge semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W11 may depend on W01-W10 public Communication Context surfaces.
 * It must remain optional and must not be required by W14 concrete bindings
 * or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TSessionRegistry final
    {
        TBoundedRegistry<TSessionId, TSession, Capacity> registry{
            TBoundedRegistry<TSessionId, TSession, Capacity>::make("session_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_session(TSession session) noexcept
        {
            return registry.register_value(
                session.session_id,
                session,
                session.session_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TSessionId, TSession>* find(
            TSessionId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TSessionId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TSessionRegistry make(
            std::string_view name = "session_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionRegistry{
                TBoundedRegistry<TSessionId, TSession, Capacity>::make(name, token)
            };
        }
    };
}

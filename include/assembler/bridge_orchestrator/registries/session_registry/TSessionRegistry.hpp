#pragma once

#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"

/**
 * @file TSessionRegistry.hpp
 * @brief Core bounded registry for ASCC session declarations.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical registry path for `TSessionRegistry`.  The previous
 * implementation lived under `registries/optional_registries/typed`; that path
 * is now compatibility-only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry groups session model values for catalog/evidence purposes. It
 * must not execute protocols, invoke endpoints, schedule runtime work, or own
 * endpoint resources.
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

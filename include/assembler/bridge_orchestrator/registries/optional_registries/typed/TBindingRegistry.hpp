#pragma once

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"

/**
 * @file TBindingRegistry.hpp
 * @brief Optional bounded registry for binding declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - typed registry over `TBindingId` and `TBinding`;
 * - compatibility-visible binding storage for diagnostics;
 * - no session materialization authority.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - alias-friendly typed wrapper;
 * - register/find helpers via composition;
 * - snapshot helper.
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
    struct TBindingRegistry final
    {
        TBoundedRegistry<TBindingId, TBinding, Capacity> registry{
            TBoundedRegistry<TBindingId, TBinding, Capacity>::make("binding_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_binding(TBinding binding) noexcept
        {
            return registry.register_value(
                binding.binding_id,
                binding,
                binding.binding_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TBindingId, TBinding>* find(
            TBindingId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TBindingId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TBindingRegistry make(
            std::string_view name = "binding_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBindingRegistry{
                TBoundedRegistry<TBindingId, TBinding, Capacity>::make(name, token)
            };
        }
    };
}

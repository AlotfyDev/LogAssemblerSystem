#pragma once

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"

/**
 * @file TBindingRegistry.hpp
 * @brief Core bounded registry for ASCC binding declarations.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical registry path for `TBindingRegistry`.  The previous
 * implementation lived under `registries/optional_registries/typed`; that path
 * is now compatibility-only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry stores binding declarations for catalog/evidence purposes.  It
 * must not materialize sessions, invoke endpoints, schedule runtime work,
 * behave as a broker, or own endpoint resources.
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

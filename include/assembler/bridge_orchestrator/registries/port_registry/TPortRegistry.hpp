#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"
#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TPortRegistry.hpp
 * @brief Core bounded registry for ASCC port views.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This registry stores bridge-visible `TPortView` values.  It does not store
 * or own concrete endpoint port objects.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not become a service locator, broker, scheduler,
 * dependency-injection container, endpoint invoker, pipeline composer, or owner
 * of endpoint lifecycle.  It only catalogs port views for ASCC
 * composition/evidence/diagnostic surfaces.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TPortRegistry final
    {
        std::array<TPortView, Capacity> ports{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view registry_name{"port_registry"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !registry_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr const TPortView* find(
            std::uint64_t port_id) const noexcept
        {
            if (port_id == 0u)
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (ports[index].port_id == port_id)
                {
                    return &ports[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool contains(std::uint64_t port_id) const noexcept
        {
            return find(port_id) != nullptr;
        }

        constexpr bool register_port(TPortView port) noexcept
        {
            if (!is_valid()
                || full()
                || !port.is_valid()
                || contains(port.port_id))
            {
                ++rejected_insertions;
                return false;
            }

            ports[count] = port;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return TRegistrySnapshot::make(
                registry_name,
                count,
                Capacity,
                rejected_insertions,
                correlation);
        }

        [[nodiscard]] static constexpr TPortRegistry make(
            std::string_view name = "port_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPortRegistry{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}

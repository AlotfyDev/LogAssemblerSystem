#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/registries/optional_registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TChannelRegistry.hpp
 * @brief Optional bounded registry for channel declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - channel-specific registry keyed by channel id;
 * - diagnostic lookup without owning channel lifecycle;
 * - no channel discovery service or channel execution behavior.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - fixed-capacity channel storage;
 * - register/find/contains/snapshot helpers;
 * - duplicate prevention by channel id.
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
    struct TChannelRegistry final
    {
        std::array<TChannel, Capacity> channels{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view registry_name{"channel_registry"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !registry_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr const TChannel* find(std::uint64_t channel_id) const noexcept
        {
            if (channel_id == 0u)
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (channels[index].channel_id == channel_id)
                {
                    return &channels[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool contains(std::uint64_t channel_id) const noexcept
        {
            return find(channel_id) != nullptr;
        }

        constexpr bool register_channel(TChannel channel) noexcept
        {
            if (!is_valid() || full() || !channel.is_valid() || contains(channel.channel_id))
            {
                ++rejected_insertions;
                return false;
            }

            channels[count] = channel;
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

        [[nodiscard]] static constexpr TChannelRegistry make(
            std::string_view name = "channel_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TChannelRegistry{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}

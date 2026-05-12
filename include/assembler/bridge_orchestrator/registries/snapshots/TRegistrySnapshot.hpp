#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TRegistrySnapshot.hpp
 * @brief Core diagnostic snapshot for ASCC registries.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This file is the canonical core-registry home for the registry snapshot
 * value that originally lived under `optional_registries/snapshots`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This snapshot exposes bounded registry diagnostics only.  It must not expose
 * endpoint internals, private storage mutation, service-location, scheduling,
 * broker behavior, or pipeline composition.
 */

namespace assembler::communication_context
{
    struct TRegistrySnapshot final
    {
        std::string_view registry_name{};
        std::size_t count{0u};
        std::size_t capacity{0u};
        std::uint64_t rejected_insertions{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !registry_name.empty() && capacity > 0u && count <= capacity;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return count == 0u;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return capacity > 0u && count >= capacity;
        }

        [[nodiscard]] static constexpr TRegistrySnapshot invalid() noexcept
        {
            return TRegistrySnapshot{};
        }

        [[nodiscard]] static constexpr TRegistrySnapshot make(
            std::string_view name,
            std::size_t current_count,
            std::size_t max_capacity,
            std::uint64_t rejected_count = 0u,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TRegistrySnapshot{
                name,
                current_count,
                max_capacity,
                rejected_count,
                token
            };
        }
    };
}

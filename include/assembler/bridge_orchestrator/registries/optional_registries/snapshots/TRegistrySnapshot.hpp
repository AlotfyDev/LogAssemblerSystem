#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TRegistrySnapshot.hpp
 * @brief Diagnostic snapshot for optional registries.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - small aggregate snapshot for registry diagnostics;
 * - capacity and count visibility;
 * - no exposure of endpoint internals or private registry storage.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - count/capacity fields;
 * - fullness/emptiness helpers;
 * - invalid and make helpers.
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

#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TIntegrationBoundaryCapability.hpp
 * @brief Capability flags for abstract integration boundary ports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - bounded bitmask vocabulary for common future integration capabilities;
 * - no implication that a concrete endpoint already exists;
 * - helpers for composing and checking capabilities.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - enum class `TIntegrationBoundaryCapability`;
 * - bitwise helpers over `std::uint32_t`;
 * - textual conversion for individual capabilities.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete persistence, telemetry, ABI, read-side, or external receiver
 *   integration;
 * - endpoint-domain internals;
 * - adapter/port call wiring for concrete endpoints;
 * - storage, database, file IO, network IO, telemetry export, or logging sinks;
 * - runtime scheduling, service location, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - bridge execution replacement;
 * - ownership over downstream lifecycle or endpoint resources.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W13 may depend on W01-W12 public Communication Context surfaces.
 * It must remain future-facing and abstract. Concrete implementations belong
 * to later dedicated binding waves.
 */

namespace assembler::communication_context
{
    enum class TIntegrationBoundaryCapability : std::uint32_t
    {
        none = 0u,
        accepts_handoff = 1u << 0u,
        completes_handoff = 1u << 1u,
        emits_acknowledgement = 1u << 2u,
        exposes_readiness = 1u << 3u,
        supports_batch = 1u << 4u,
        supports_ordering = 1u << 5u,
        supports_backpressure = 1u << 6u,
        supports_diagnostics = 1u << 7u
    };

    [[nodiscard]] constexpr std::uint32_t to_mask(
        TIntegrationBoundaryCapability capability) noexcept
    {
        return static_cast<std::uint32_t>(capability);
    }

    [[nodiscard]] constexpr std::uint32_t operator|(
        TIntegrationBoundaryCapability lhs,
        TIntegrationBoundaryCapability rhs) noexcept
    {
        return to_mask(lhs) | to_mask(rhs);
    }


    [[nodiscard]] constexpr std::uint32_t operator|(
        std::uint32_t lhs,
        TIntegrationBoundaryCapability rhs) noexcept
    {
        return lhs | to_mask(rhs);
    }

    [[nodiscard]] constexpr std::uint32_t operator|(
        TIntegrationBoundaryCapability lhs,
        std::uint32_t rhs) noexcept
    {
        return to_mask(lhs) | rhs;
    }

    [[nodiscard]] constexpr std::uint32_t add_capability(
        std::uint32_t mask,
        TIntegrationBoundaryCapability capability) noexcept
    {
        return mask | to_mask(capability);
    }

    [[nodiscard]] constexpr bool has_capability(
        std::uint32_t mask,
        TIntegrationBoundaryCapability capability) noexcept
    {
        return (mask & to_mask(capability)) == to_mask(capability);
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TIntegrationBoundaryCapability capability) noexcept
    {
        switch (capability)
        {
            case TIntegrationBoundaryCapability::none: return "none";
            case TIntegrationBoundaryCapability::accepts_handoff: return "accepts_handoff";
            case TIntegrationBoundaryCapability::completes_handoff: return "completes_handoff";
            case TIntegrationBoundaryCapability::emits_acknowledgement: return "emits_acknowledgement";
            case TIntegrationBoundaryCapability::exposes_readiness: return "exposes_readiness";
            case TIntegrationBoundaryCapability::supports_batch: return "supports_batch";
            case TIntegrationBoundaryCapability::supports_ordering: return "supports_ordering";
            case TIntegrationBoundaryCapability::supports_backpressure: return "supports_backpressure";
            case TIntegrationBoundaryCapability::supports_diagnostics: return "supports_diagnostics";
        }

        return "none";
    }
}

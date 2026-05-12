#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TPlacementHandle.hpp
 * @brief Opaque host-placement handle carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - opaque bridge-visible placement reference produced by a host-side port;
 * - safe correlation between a placement request and later load signals;
 * - future support for host-specific handle families without exposing host
 *   private pointers, slots, containers, or round managers.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - opaque numeric handle value;
 * - handle-family label;
 * - correlation token;
 * - validity/equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - direct Slot, SlotsContainer, RoundManager, or Moderator references.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TPlacementHandle final
    {
        std::uint64_t value{0};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view handle_family{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u && correlation.is_valid();
        }

        [[nodiscard]] static constexpr TPlacementHandle invalid() noexcept
        {
            return TPlacementHandle{0u, TCorrelationToken::invalid(), {}};
        }

        [[nodiscard]] static constexpr TPlacementHandle make(
            std::uint64_t opaque_value,
            TCorrelationToken token,
            std::string_view family = {}) noexcept
        {
            return TPlacementHandle{opaque_value, token, family};
        }

        friend constexpr bool operator==(
            const TPlacementHandle& lhs,
            const TPlacementHandle& rhs) noexcept
        {
            return lhs.value == rhs.value && lhs.correlation == rhs.correlation;
        }

        friend constexpr bool operator!=(
            const TPlacementHandle& lhs,
            const TPlacementHandle& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
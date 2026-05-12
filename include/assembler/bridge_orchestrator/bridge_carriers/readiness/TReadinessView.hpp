#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TReadinessView.hpp
 * @brief Read-only bridge-visible readiness carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - read-only readiness projection for a participant, port, adapter, binding,
 *   or protocol-facing endpoint surface;
 * - future extensibility for capacity, backpressure, deferral, and diagnostic
 *   projection without exposing endpoint internals;
 * - safe bridge-visible status used before admission or signal exchange.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - readiness enum;
 * - optional capacity hint;
 * - optional reason text;
 * - correlation-aware readiness view.
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
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TReadinessState
    {
        unknown,
        ready,
        not_ready,
        deferred,
        saturated
    };

    struct TReadinessView final
    {
        TReadinessState state{TReadinessState::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::uint64_t capacity_hint{0};
        std::string_view reason{};

        [[nodiscard]] constexpr bool is_ready() const noexcept
        {
            return state == TReadinessState::ready;
        }

        [[nodiscard]] constexpr bool is_deferred() const noexcept
        {
            return state == TReadinessState::deferred;
        }

        [[nodiscard]] static constexpr TReadinessView ready(
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::uint64_t capacity = 0u) noexcept
        {
            return TReadinessView{TReadinessState::ready, token, capacity, {}};
        }

        [[nodiscard]] static constexpr TReadinessView not_ready(
            std::string_view why = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TReadinessView{TReadinessState::not_ready, token, 0u, why};
        }

        [[nodiscard]] static constexpr TReadinessView deferred(
            std::string_view why = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TReadinessView{TReadinessState::deferred, token, 0u, why};
        }
    };
}
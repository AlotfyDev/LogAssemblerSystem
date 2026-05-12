#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TRegistryLookupResult.hpp
 * @brief Lookup result metadata for optional registries.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - registry lookup diagnostics without leaking storage internals;
 * - explicit found/not-found/rejected status;
 * - optional error reason for diagnostic callers.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - lightweight lookup metadata value;
 * - factory helpers for found, missing, rejected;
 * - success/failure helpers.
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
    struct TRegistryLookupResult final
    {
        bool found{false};
        bool rejected{false};
        std::string_view registry_name{};
        std::string_view note{};
        TBridgeError reason{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return found && !rejected;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !succeeded();
        }

        [[nodiscard]] static constexpr TRegistryLookupResult found_result(
            std::string_view name,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "registry lookup found entry") noexcept
        {
            return TRegistryLookupResult{
                true,
                false,
                name,
                text,
                TBridgeError{},
                token
            };
        }

        [[nodiscard]] static constexpr TRegistryLookupResult missing(
            std::string_view name,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "registry lookup did not find entry") noexcept
        {
            return TRegistryLookupResult{
                false,
                false,
                name,
                text,
                TBridgeError{},
                token
            };
        }

        [[nodiscard]] static constexpr TRegistryLookupResult reject(
            std::string_view name,
            TBridgeError error,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TRegistryLookupResult{
                false,
                true,
                name,
                error.message,
                error,
                token
            };
        }
    };
}

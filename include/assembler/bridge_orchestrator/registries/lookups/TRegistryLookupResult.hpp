#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TRegistryLookupResult.hpp
 * @brief Core registry lookup result metadata for ASCC registries.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This file is the canonical core-registry home for the lookup-result value
 * that originally lived under `optional_registries/lookups`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This value reports lookup outcome only.  It must not implement service
 * location, endpoint invocation, scheduling, persistence, broker behavior, or
 * pipeline composition.
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

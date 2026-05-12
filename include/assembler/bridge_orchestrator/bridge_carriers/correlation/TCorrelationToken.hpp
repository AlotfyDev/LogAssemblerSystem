#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>

/**
 * @file TCorrelationToken.hpp
 * @brief Bridge-visible correlation token primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - stable correlation identity for bridge-visible carriers;
 * - opaque correlation representation independent from endpoint internals;
 * - safe equality, validity, and hashing support;
 * - future traceability hooks without changing endpoint ownership.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - two 64-bit opaque token parts;
 * - constexpr invalid-token construction;
 * - constexpr validity and equality helpers;
 * - standard hash specialization support.
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
    struct TCorrelationToken final
    {
        std::uint64_t high{0};
        std::uint64_t low{0};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return high != 0u || low != 0u;
        }

        [[nodiscard]] static constexpr TCorrelationToken invalid() noexcept
        {
            return TCorrelationToken{0u, 0u};
        }

        [[nodiscard]] static constexpr TCorrelationToken from_parts(
            std::uint64_t high_part,
            std::uint64_t low_part) noexcept
        {
            return TCorrelationToken{high_part, low_part};
        }

        friend constexpr bool operator==(
            const TCorrelationToken& lhs,
            const TCorrelationToken& rhs) noexcept
        {
            return lhs.high == rhs.high && lhs.low == rhs.low;
        }

        friend constexpr bool operator!=(
            const TCorrelationToken& lhs,
            const TCorrelationToken& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}

namespace std
{
    template<>
    struct hash<assembler::communication_context::TCorrelationToken>
    {
        [[nodiscard]] std::size_t operator()(
            const assembler::communication_context::TCorrelationToken& token) const noexcept
        {
            const auto h1 = std::hash<std::uint64_t>{}(token.high);
            const auto h2 = std::hash<std::uint64_t>{}(token.low);
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6u) + (h1 >> 2u));
        }
    };
}
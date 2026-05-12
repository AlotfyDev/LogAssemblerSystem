#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TLogLevelEnvelopeDescriptor.hpp
 * @brief Bridge-visible descriptor for a Log Level Envelope payload.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - endpoint-neutral descriptor of a prepared Log Level Envelope;
 * - stable payload-kind, envelope identity, size hint, ordering hint, and
 *   destination-family projection;
 * - no ownership of the real envelope object and no exposure of Log Level API
 *   internals.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - lightweight descriptor fields;
 * - validity helper;
 * - static factory for prepared-envelope descriptor.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Log Level API facade implementation;
 * - Envelope Assembler internals;
 * - content validation internals;
 * - metadata injection or timestamp stabilization internals;
 * - Write Side placement port implementation;
 * - Write Side slot/container/round internals;
 * - bridge orchestration beyond W10 model stepping;
 * - registry, database, persistence, telemetry, scheduler, thread, or ABI behavior;
 * - dynamic plugin loading or runtime dependency injection.
 * - raw envelope storage or full envelope schema.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14A concrete adapter headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPluginAdapter` obligations, and W10 aggregate bridge
 * surfaces for smoke-test compatibility. They must not include concrete
 * `assembler/log_level_api/...` or `assembler/write_side/...` endpoint-domain
 * internals until those domains are separately realized and explicitly bridged.
 */

namespace assembler::communication_context
{
    struct TLogLevelEnvelopeDescriptor final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view envelope_id{};
        std::string_view envelope_kind{"log_level_envelope"};
        std::uint64_t payload_size_hint{0u};
        bool requires_ordered_placement{true};
        std::string_view requested_destination_family{"write_side"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid()
                && !envelope_id.empty()
                && !envelope_kind.empty();
        }

        [[nodiscard]] static constexpr TLogLevelEnvelopeDescriptor make(
            TCorrelationToken token,
            std::string_view id,
            std::uint64_t size_hint = 0u,
            bool ordered = true,
            std::string_view destination_family = "write_side",
            std::string_view kind = "log_level_envelope") noexcept
        {
            return TLogLevelEnvelopeDescriptor{
                token,
                id,
                kind,
                size_hint,
                ordered,
                destination_family
            };
        }
    };
}

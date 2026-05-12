#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TChannelProfile.hpp
 * @brief Bridge-visible channel profile vocabulary and descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative channel-foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical vocabulary for channel topology shapes;
 * - bridge-visible profile descriptor usable by channel topology, compatibility,
 *   binding policy, sessions, protocols, registries, and diagnostics;
 * - future support for one-to-one, one-to-many, many-to-one, many-to-many,
 *   broadcast, fan-in, fan-out, and staged pipeline profiles without turning
 *   channels into sessions or brokers.
 *
 * @section ascc_current_wave Current W04 Implementation Scope
 * This W04 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable channel profile,
 * channel binding policy, and channel topology values without session
 * execution, binding execution, bridge orchestration, or endpoint-domain
 * dependency.
 *
 * - channel profile kind enum;
 * - multiplicity and direction classification helpers;
 * - lightweight channel profile value object;
 * - stable profile-name projection.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - adapter or port obligation implementation;
 * - concrete adapter-port binding execution;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This channel foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, and W03 participant descriptors.
 * It must not include endpoint-domain headers such as log_level_api, write_side,
 * read_side, persistence implementations, telemetry SDKs, or thin C ABI
 * implementation internals.
 */

namespace assembler::communication_context
{
    enum class TChannelProfileKind
    {
        unknown,

        single_adapter_single_port,
        single_adapter_many_ports,
        many_adapters_single_port,
        many_adapters_many_ports,

        fan_out,
        fan_in,
        broadcast,
        staged_pipeline
    };

    enum class TChannelDirection
    {
        unknown,
        unidirectional,
        bidirectional,
        observer_only
    };

    struct TChannelProfile final
    {
        TChannelProfileKind kind{TChannelProfileKind::unknown};
        TChannelDirection direction{TChannelDirection::unknown};
        std::uint32_t min_adapters{0};
        std::uint32_t max_adapters{0};
        std::uint32_t min_ports{0};
        std::uint32_t max_ports{0};
        std::string_view profile_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return kind != TChannelProfileKind::unknown
                && direction != TChannelDirection::unknown
                && min_adapters <= max_adapters
                && min_ports <= max_ports
                && max_adapters > 0u
                && max_ports > 0u;
        }

        [[nodiscard]] constexpr bool is_single_adapter() const noexcept
        {
            return min_adapters == 1u && max_adapters == 1u;
        }

        [[nodiscard]] constexpr bool is_single_port() const noexcept
        {
            return min_ports == 1u && max_ports == 1u;
        }

        [[nodiscard]] constexpr bool is_one_to_one() const noexcept
        {
            return is_single_adapter() && is_single_port();
        }

        [[nodiscard]] constexpr bool allows_multiple_adapters() const noexcept
        {
            return max_adapters > 1u;
        }

        [[nodiscard]] constexpr bool allows_multiple_ports() const noexcept
        {
            return max_ports > 1u;
        }

        [[nodiscard]] static constexpr TChannelProfile make(
            TChannelProfileKind profile_kind,
            TChannelDirection channel_direction,
            std::uint32_t minimum_adapters,
            std::uint32_t maximum_adapters,
            std::uint32_t minimum_ports,
            std::uint32_t maximum_ports,
            std::string_view name = {}) noexcept
        {
            return TChannelProfile{
                profile_kind,
                channel_direction,
                minimum_adapters,
                maximum_adapters,
                minimum_ports,
                maximum_ports,
                name
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(TChannelProfileKind kind) noexcept
    {
        switch (kind)
        {
            case TChannelProfileKind::unknown: return "unknown";
            case TChannelProfileKind::single_adapter_single_port: return "single_adapter_single_port";
            case TChannelProfileKind::single_adapter_many_ports: return "single_adapter_many_ports";
            case TChannelProfileKind::many_adapters_single_port: return "many_adapters_single_port";
            case TChannelProfileKind::many_adapters_many_ports: return "many_adapters_many_ports";
            case TChannelProfileKind::fan_out: return "fan_out";
            case TChannelProfileKind::fan_in: return "fan_in";
            case TChannelProfileKind::broadcast: return "broadcast";
            case TChannelProfileKind::staged_pipeline: return "staged_pipeline";
        }

        return "unknown";
    }

    [[nodiscard]] constexpr std::string_view to_string(TChannelDirection direction) noexcept
    {
        switch (direction)
        {
            case TChannelDirection::unknown: return "unknown";
            case TChannelDirection::unidirectional: return "unidirectional";
            case TChannelDirection::bidirectional: return "bidirectional";
            case TChannelDirection::observer_only: return "observer_only";
        }

        return "unknown";
    }
}
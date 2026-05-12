#pragma once

#include "assembler/communication_context/channels/profiles/TChannelProfile.hpp"

/**
 * @file TSingleAdapterSinglePortProfile.hpp
 * @brief Canonical one-adapter/one-port channel profile preset.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative channel-foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical profile preset for the initial valid ASCC communication shape:
 *   one content-provider plugin adapter bound to one host-provider port;
 * - stable profile used by early envelope-placement modeling;
 * - future comparison baseline for richer one-to-many, many-to-one, and
 *   staged channel profiles.
 *
 * @section ascc_current_wave Current W04 Implementation Scope
 * This W04 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable channel profile,
 * channel binding policy, and channel topology values without session
 * execution, binding execution, bridge orchestration, or endpoint-domain
 * dependency.
 *
 * - constexpr factory for single-adapter/single-port profile;
 * - constexpr classification helper;
 * - no session or binding execution.
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
    struct TSingleAdapterSinglePortProfile final
    {
        [[nodiscard]] static constexpr TChannelProfile make() noexcept
        {
            return TChannelProfile::make(
                TChannelProfileKind::single_adapter_single_port,
                TChannelDirection::unidirectional,
                1u,
                1u,
                1u,
                1u,
                "single_adapter_single_port");
        }

        [[nodiscard]] static constexpr bool matches(
            const TChannelProfile& profile) noexcept
        {
            return profile.kind == TChannelProfileKind::single_adapter_single_port
                && profile.direction == TChannelDirection::unidirectional
                && profile.is_one_to_one();
        }
    };
}
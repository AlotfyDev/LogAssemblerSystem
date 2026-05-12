#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/channels/profiles/TChannelProfile.hpp"

/**
 * @file TChannelBindingPolicy.hpp
 * @brief Bridge-visible channel binding policy value.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative channel-foundation
 * definition for its Communication Context concept when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical channel-level policy controlling how participants, future
 *   plugin adapters, and future ports may be associated under a channel;
 * - future support for strict one-to-one binding, deferred binding, static
 *   binding, dynamic binding, fan-out/fan-in constraints, visibility limits,
 *   and compatibility preconditions;
 * - policy surface for channel topology, not endpoint behavior.
 *
 * @section ascc_current_wave Current W04 Implementation Scope
 * This W04 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable channel profile,
 * channel binding policy, and channel topology values without session
 * execution, binding execution, bridge orchestration, or endpoint-domain
 * dependency.
 *
 * - binding mode enum;
 * - lifecycle mode enum;
 * - visibility mode enum;
 * - lightweight policy value with compatibility against a channel profile.
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
 * - final adapter-port binding objects or binding execution.
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
    enum class TChannelBindingMode
    {
        unknown,
        strict_one_to_one,
        one_adapter_to_many_ports,
        many_adapters_to_one_port,
        many_to_many,
        observer_only
    };

    enum class TChannelBindingLifecycle
    {
        unknown,
        static_binding,
        deferred_binding,
        dynamic_binding
    };

    enum class TChannelVisibility
    {
        unknown,
        private_channel,
        domain_local,
        cross_domain,
        boundary_facing
    };

    struct TChannelBindingPolicy final
    {
        TChannelBindingMode binding_mode{TChannelBindingMode::unknown};
        TChannelBindingLifecycle lifecycle{TChannelBindingLifecycle::unknown};
        TChannelVisibility visibility{TChannelVisibility::unknown};
        bool require_compatible_roles{true};
        bool require_compatible_carriers{true};
        bool allow_rebinding{false};
        std::uint32_t max_active_bindings{1};
        std::string_view policy_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return binding_mode != TChannelBindingMode::unknown
                && lifecycle != TChannelBindingLifecycle::unknown
                && visibility != TChannelVisibility::unknown
                && max_active_bindings > 0u;
        }

        [[nodiscard]] constexpr bool is_static() const noexcept
        {
            return lifecycle == TChannelBindingLifecycle::static_binding;
        }

        [[nodiscard]] constexpr bool is_dynamic() const noexcept
        {
            return lifecycle == TChannelBindingLifecycle::dynamic_binding;
        }

        [[nodiscard]] constexpr bool is_strict_one_to_one() const noexcept
        {
            return binding_mode == TChannelBindingMode::strict_one_to_one
                && max_active_bindings == 1u;
        }

        [[nodiscard]] constexpr bool is_compatible_with(
            const TChannelProfile& profile) const noexcept
        {
            if (!is_valid() || !profile.is_valid())
            {
                return false;
            }

            if (binding_mode == TChannelBindingMode::strict_one_to_one)
            {
                return profile.is_one_to_one();
            }

            if (binding_mode == TChannelBindingMode::one_adapter_to_many_ports)
            {
                return profile.is_single_adapter() && profile.allows_multiple_ports();
            }

            if (binding_mode == TChannelBindingMode::many_adapters_to_one_port)
            {
                return profile.allows_multiple_adapters() && profile.is_single_port();
            }

            if (binding_mode == TChannelBindingMode::many_to_many)
            {
                return profile.allows_multiple_adapters() && profile.allows_multiple_ports();
            }

            if (binding_mode == TChannelBindingMode::observer_only)
            {
                return profile.direction == TChannelDirection::observer_only;
            }

            return false;
        }

        [[nodiscard]] static constexpr TChannelBindingPolicy strict_static_one_to_one(
            TChannelVisibility channel_visibility = TChannelVisibility::cross_domain,
            std::string_view name = "strict_static_one_to_one") noexcept
        {
            return TChannelBindingPolicy{
                TChannelBindingMode::strict_one_to_one,
                TChannelBindingLifecycle::static_binding,
                channel_visibility,
                true,
                true,
                false,
                1u,
                name
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(TChannelBindingMode mode) noexcept
    {
        switch (mode)
        {
            case TChannelBindingMode::unknown: return "unknown";
            case TChannelBindingMode::strict_one_to_one: return "strict_one_to_one";
            case TChannelBindingMode::one_adapter_to_many_ports: return "one_adapter_to_many_ports";
            case TChannelBindingMode::many_adapters_to_one_port: return "many_adapters_to_one_port";
            case TChannelBindingMode::many_to_many: return "many_to_many";
            case TChannelBindingMode::observer_only: return "observer_only";
        }

        return "unknown";
    }

    [[nodiscard]] constexpr std::string_view to_string(TChannelBindingLifecycle lifecycle) noexcept
    {
        switch (lifecycle)
        {
            case TChannelBindingLifecycle::unknown: return "unknown";
            case TChannelBindingLifecycle::static_binding: return "static_binding";
            case TChannelBindingLifecycle::deferred_binding: return "deferred_binding";
            case TChannelBindingLifecycle::dynamic_binding: return "dynamic_binding";
        }

        return "unknown";
    }

    [[nodiscard]] constexpr std::string_view to_string(TChannelVisibility visibility) noexcept
    {
        switch (visibility)
        {
            case TChannelVisibility::unknown: return "unknown";
            case TChannelVisibility::private_channel: return "private_channel";
            case TChannelVisibility::domain_local: return "domain_local";
            case TChannelVisibility::cross_domain: return "cross_domain";
            case TChannelVisibility::boundary_facing: return "boundary_facing";
        }

        return "unknown";
    }
}
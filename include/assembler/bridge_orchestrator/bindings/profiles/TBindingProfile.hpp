#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TBindingProfile.hpp
 * @brief Binding profile and binding-kind declaration model.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - canonical profile for binding declaration constraints;
 * - future support for strict one-to-one, one-to-many, many-to-one,
 *   many-to-many, observer-only, static, and dynamic binding policies;
 * - bridge-visible binding metadata without owning channel topology or
 *   endpoint internals.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - binding kind enum;
 * - binding profile value with cardinality, compatibility, and session
 *   readiness flags;
 * - strict one-to-one static helper aligned with W04 and W05 foundations.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol execution or bridge orchestration;
 * - endpoint validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - channel registry, binding registry, or runtime routing table.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This binding model header may depend on W01 primitive carriers/results,
 * W02 protocol-state categories where needed, W03 participants, W04 channel
 * topology, and W05 obligation-surface views. It must not include endpoint
 * domain headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBindingKind
    {
        unknown,
        strict_one_to_one,
        one_adapter_to_many_ports,
        many_adapters_to_one_port,
        many_to_many,
        observer_only
    };

    struct TBindingProfile final
    {
        TBindingKind kind{TBindingKind::unknown};
        bool require_channel_valid{true};
        bool require_channel_declared{true};
        bool require_surface_pair_valid{true};
        bool require_primary_placement_flow{true};
        bool allow_session_materialization{false};
        bool allow_rebinding{false};
        std::uint32_t profile_version{1u};
        std::string_view profile_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return kind != TBindingKind::unknown
                && profile_version > 0u;
        }

        [[nodiscard]] constexpr bool is_strict_one_to_one() const noexcept
        {
            return kind == TBindingKind::strict_one_to_one
                && require_channel_valid
                && require_surface_pair_valid;
        }

        [[nodiscard]] static constexpr TBindingProfile strict_static_one_to_one(
            std::string_view name = "strict_static_one_to_one_binding") noexcept
        {
            return TBindingProfile{
                TBindingKind::strict_one_to_one,
                true,
                true,
                true,
                true,
                false,
                false,
                1u,
                name
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(TBindingKind kind) noexcept
    {
        switch (kind)
        {
            case TBindingKind::unknown: return "unknown";
            case TBindingKind::strict_one_to_one: return "strict_one_to_one";
            case TBindingKind::one_adapter_to_many_ports: return "one_adapter_to_many_ports";
            case TBindingKind::many_adapters_to_one_port: return "many_adapters_to_one_port";
            case TBindingKind::many_to_many: return "many_to_many";
            case TBindingKind::observer_only: return "observer_only";
        }

        return "unknown";
    }
}
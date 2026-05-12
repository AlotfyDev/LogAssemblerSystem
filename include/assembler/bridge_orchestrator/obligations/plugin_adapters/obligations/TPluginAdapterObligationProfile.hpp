#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TPluginAdapterObligationProfile.hpp
 * @brief Content-side plugin-adapter obligation profile descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical declaration of which content-side plugin-adapter obligations a
 *   concrete adapter claims to provide;
 * - future support for envelope producers, read-side producers, telemetry
 *   producers, replay producers, and ABI-facing producers;
 * - compatibility input for future binding and bridge setup logic without
 *   executing the binding.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - plugin-adapter obligation family enum;
 * - obligation profile flags for readiness, placement-request preparation,
 *   placement-handle acceptance, load-signal emission, and next-destination
 *   request production;
 * - profile validity and primary-placement helper methods.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - concrete adapter-port binding execution;
 * - channel registry or binding registry ownership;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - content validation, payload ownership, or envelope assembly.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This obligation foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, W03 participant descriptors, and
 * W04 channel topology where needed. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TPluginAdapterObligationFamily
    {
        unknown,
        placement_content_provider,
        delivery_content_provider,
        persistence_content_provider,
        telemetry_content_provider,
        abi_boundary_content_provider,
        receiver_content_provider
    };

    struct TPluginAdapterObligationProfile final
    {
        TPluginAdapterObligationFamily family{TPluginAdapterObligationFamily::unknown};
        bool provides_readiness_view{false};
        bool prepares_placement_request{false};
        bool accepts_placement_handle{false};
        bool emits_load_signal{false};
        bool can_request_next_destination{false};
        std::uint32_t obligation_version{1u};
        std::string_view profile_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return family != TPluginAdapterObligationFamily::unknown
                && obligation_version > 0u
                && (provides_readiness_view
                    || prepares_placement_request
                    || accepts_placement_handle
                    || emits_load_signal
                    || can_request_next_destination);
        }

        [[nodiscard]] constexpr bool supports_primary_placement_flow() const noexcept
        {
            return family == TPluginAdapterObligationFamily::placement_content_provider
                && provides_readiness_view
                && prepares_placement_request
                && accepts_placement_handle
                && emits_load_signal
                && can_request_next_destination;
        }

        [[nodiscard]] static constexpr TPluginAdapterObligationProfile placement_content_provider(
            std::string_view name = "placement_content_plugin_adapter") noexcept
        {
            return TPluginAdapterObligationProfile{
                TPluginAdapterObligationFamily::placement_content_provider,
                true,
                true,
                true,
                true,
                true,
                1u,
                name
            };
        }
    };

    [[nodiscard]] constexpr std::string_view to_string(TPluginAdapterObligationFamily family) noexcept
    {
        switch (family)
        {
            case TPluginAdapterObligationFamily::unknown: return "unknown";
            case TPluginAdapterObligationFamily::placement_content_provider: return "placement_content_provider";
            case TPluginAdapterObligationFamily::delivery_content_provider: return "delivery_content_provider";
            case TPluginAdapterObligationFamily::persistence_content_provider: return "persistence_content_provider";
            case TPluginAdapterObligationFamily::telemetry_content_provider: return "telemetry_content_provider";
            case TPluginAdapterObligationFamily::abi_boundary_content_provider: return "abi_boundary_content_provider";
            case TPluginAdapterObligationFamily::receiver_content_provider: return "receiver_content_provider";
        }

        return "unknown";
    }
}
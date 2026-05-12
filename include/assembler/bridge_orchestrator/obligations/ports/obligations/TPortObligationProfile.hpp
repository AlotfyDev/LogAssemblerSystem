#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TPortObligationProfile.hpp
 * @brief Host-side port obligation profile descriptor.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical declaration of which host-side obligations a concrete port
 *   claims to provide;
 * - future support for placement, delivery, persistence, telemetry, ABI, and
 *   receiver-facing port obligation families;
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
 * - host-side port obligation family enum;
 * - obligation profile flags for readiness, admission, handle production,
 *   load-signal acceptance, and next-destination planning;
 * - profile validity and capability helper methods.
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
 * - concrete host-side placement or storage behavior.
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
    enum class TPortObligationFamily
    {
        unknown,
        placement_host,
        delivery_host,
        persistence_host,
        telemetry_host,
        abi_boundary_host,
        receiver_host
    };

    struct TPortObligationProfile final
    {
        TPortObligationFamily family{TPortObligationFamily::unknown};
        bool provides_readiness_view{false};
        bool accepts_placement_request{false};
        bool produces_placement_handle{false};
        bool accepts_load_signal{false};
        bool supports_next_destination_request{false};
        std::uint32_t obligation_version{1u};
        std::string_view profile_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return family != TPortObligationFamily::unknown
                && obligation_version > 0u
                && (provides_readiness_view
                    || accepts_placement_request
                    || produces_placement_handle
                    || accepts_load_signal
                    || supports_next_destination_request);
        }

        [[nodiscard]] constexpr bool supports_primary_placement_flow() const noexcept
        {
            return family == TPortObligationFamily::placement_host
                && provides_readiness_view
                && accepts_placement_request
                && produces_placement_handle
                && accepts_load_signal;
        }

        [[nodiscard]] static constexpr TPortObligationProfile placement_host(
            std::string_view name = "placement_host_port") noexcept
        {
            return TPortObligationProfile{
                TPortObligationFamily::placement_host,
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

    [[nodiscard]] constexpr std::string_view to_string(TPortObligationFamily family) noexcept
    {
        switch (family)
        {
            case TPortObligationFamily::unknown: return "unknown";
            case TPortObligationFamily::placement_host: return "placement_host";
            case TPortObligationFamily::delivery_host: return "delivery_host";
            case TPortObligationFamily::persistence_host: return "persistence_host";
            case TPortObligationFamily::telemetry_host: return "telemetry_host";
            case TPortObligationFamily::abi_boundary_host: return "abi_boundary_host";
            case TPortObligationFamily::receiver_host: return "receiver_host";
        }

        return "unknown";
    }
}
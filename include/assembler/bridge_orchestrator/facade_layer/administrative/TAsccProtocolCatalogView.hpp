#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TAsccProtocolCatalogView.hpp
 * @brief Administrative facade view for ASCC-supported protocol families.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccProtocolCatalogView` is part of the ASCC Administrative Facade.
 * It exposes, in a bounded and read-only form, which protocol families the
 * Communication Context component declares as administratively known and
 * potentially selectable by a higher-level Pipeline Composer.
 *
 * The catalog is not a protocol executor. It does not create sessions, advance
 * protocol state, validate participant capabilities, move carriers, invoke
 * adapters, call ports, or open bridge runtime paths. It is a component-facing
 * declaration surface.
 *
 * @section ascc_facade_layer_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/administrative/
 * ```
 *
 * Administrative surface answers:
 *
 * ```text
 * What protocol families does this ASCC component declare as supported or
 * known at the component boundary?
 * ```
 *
 * It is consumed by the Pipeline Composer before managerial admission. The
 * Pipeline Composer should use this view to determine whether an ASCC component
 * can even be considered for a pipeline profile that requires a specific
 * protocol family.
 *
 * @section relationship_to_protocols Relationship To Protocol Model Entities
 * The catalog refers to `TBridgeProtocolKind`, which is the protocol-family
 * vocabulary already defined under `protocols/kinds/`.
 *
 * The catalog deliberately does not expose raw `TBridgeProtocol` objects, raw
 * `TBridgeProtocolPlan` storage, or mutable protocol state. Those belong to the
 * protocol model and runtime path, not to administrative discovery.
 *
 * Expected future relationships:
 *
 * ```text
 * TAsccProtocolCatalogView
 *     -> TBridgeProtocolKind
 *     -> TBridgeProtocolPlan catalog entries
 *     -> TProtocolRequirementSet catalog entries
 *     -> TAsccProtocolReadinessView during managerial admission
 * ```
 *
 * In the final mature design, this view may be paired with a richer protocol
 * profile catalog that references default plans, requirement-set identifiers,
 * protocol version metadata, compatibility notes, and optional feature flags.
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * This administrative catalog feeds the managerial facade. It does not decide
 * readiness itself.
 *
 * ```text
 * TAsccProtocolCatalogView
 *     -> TAsccProtocolAdmissionPolicy
 *     -> TAsccProtocolReadinessView
 *     -> TAsccManagerialReadinessView
 * ```
 *
 * The consuming facade must not use this catalog as an operation entry point.
 * Consuming surfaces operate only after administrative declaration and
 * managerial admission are complete.
 *
 * @section policy_relationship Policy Relationship
 * Policy belongs primarily to the composition layer. This catalog supplies
 * policy-realizable protocol capabilities. It does not own policy semantics and
 * must not become a policy executor.
 *
 * Example:
 *
 * ```text
 * A composition policy requires envelope_placement.
 * Pipeline Composer checks TAsccProtocolCatalogView for envelope_placement.
 * Managerial facade then validates requirements/readiness.
 * Consuming facade later runs only the admitted profile.
 * ```
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol state advancement;
 * - bridge execution;
 * - endpoint invocation;
 * - adapter or port calls;
 * - participant resolution;
 * - requirement matching;
 * - carrier movement;
 * - policy assignment;
 * - dynamic registry ownership;
 * - scheduler, worker, thread, async, IO, persistence, or telemetry behavior.
 *
 * @section current_shape Current Shape
 * The current implementation is intentionally bounded/static-friendly and
 * header-only. It stores protocol kinds directly. Later waves may replace or
 * supplement this with typed catalog entries, profile IDs, and requirement-set
 * references without changing the facade responsibility.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccProtocolCatalogView final
    {
        std::array<TBridgeProtocolKind, Capacity> protocol_kinds{};
        std::size_t count{0u};
        std::string_view catalog_name{"ascc_protocol_catalog"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return count <= Capacity && !catalog_name.empty();
        }

        constexpr bool add(TBridgeProtocolKind kind) noexcept
        {
            if (count >= Capacity || kind == TBridgeProtocolKind::unknown)
            {
                return false;
            }

            protocol_kinds[count++] = kind;
            return true;
        }

        [[nodiscard]] constexpr bool supports(TBridgeProtocolKind kind) const noexcept
        {
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (protocol_kinds[index] == kind)
                {
                    return true;
                }
            }

            return false;
        }

        [[nodiscard]] static constexpr TAsccProtocolCatalogView envelope_placement_only(
            std::string_view name = "ascc_envelope_placement_protocol_catalog") noexcept
        {
            TAsccProtocolCatalogView<Capacity> view{{}, 0u, name};
            view.add(TBridgeProtocolKind::envelope_placement);
            return view;
        }
    };
}

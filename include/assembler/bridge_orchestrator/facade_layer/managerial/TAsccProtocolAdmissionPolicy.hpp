#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/administrative/TAsccProtocolCatalogView.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccProtocolReadinessView.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementReport.hpp"

/**
 * @file TAsccProtocolAdmissionPolicy.hpp
 * @brief Managerial facade policy for admitting a selected protocol family.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccProtocolAdmissionPolicy` is the ASCC Managerial Facade policy that
 * converts administrative protocol availability and requirement/readiness
 * evidence into a protocol admission decision.
 *
 * It is not the protocol runtime. It does not advance protocol state. It does
 * not call adapters, ports, endpoints, or carriers. It decides whether a
 * selected protocol family may be admitted into a configured ASCC component
 * profile.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * It sits between:
 *
 * ```text
 * Administrative protocol declaration
 *     -> Managerial admission/readiness
 *     -> Consuming operation
 * ```
 *
 * @section relationship_to_administrative_catalog Relationship To Administrative Catalog
 * The policy consumes `TAsccProtocolCatalogView`, which answers whether a
 * protocol family is administratively known/supported by the ASCC component.
 *
 * A protocol cannot be admitted if it is not declared in the administrative
 * catalog. This keeps Pipeline Composer decisions bound to the component's
 * public facade rather than to protocol internals.
 *
 * @section relationship_to_requirements Relationship To Requirement Reports
 * The policy consumes `TProtocolRequirementReport`. That report summarizes the
 * result of matching protocol requirements against available participant,
 * carrier, and binding capabilities.
 *
 * The policy does not perform detailed matching itself in this first shape.
 * A later `TProtocolRequirementMatcher` or `TProtocolRequirementFacadeAdapter`
 * may compute the report. This policy performs admission based on the supplied
 * report and readiness flags.
 *
 * @section relationship_to_protocol_runtime Relationship To Protocol Runtime
 * This policy precedes creation or operation of a consuming protocol path.
 * `TBridgeProtocol` remains the runtime model object. This admission policy
 * decides whether the selected protocol is allowed to participate in the ASCC
 * component profile before runtime consumption.
 *
 * The intended relationship is:
 *
 * ```text
 * TAsccProtocolCatalogView
 *     + TProtocolRequirementReport
 *     + plan/binding/participant readiness flags
 *     -> TAsccProtocolAdmissionPolicy::admit(...)
 *     -> TAsccProtocolReadinessView
 *     -> TAsccManagerialReadinessView
 *     -> TAsccConsumingFacade
 * ```
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may require a certain protocol behavior. This policy
 * does not interpret governance policy semantics directly. It only admits or
 * rejects a selected protocol configuration using ASCC component evidence.
 *
 * In other words:
 *
 * ```text
 * Policy selects desired protocol profile at composition layer.
 * ASCC protocol admission policy reports whether ASCC can realize it.
 * ```
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol state transition;
 * - bridge step execution;
 * - adapter/port invocation;
 * - endpoint callback execution;
 * - participant discovery outside supplied evidence;
 * - carrier transfer;
 * - global policy assignment;
 * - persistence, telemetry, IO, threading, or async runtime.
 *
 * @section mature_shape Final Intended Shape
 * A mature policy may consume:
 *
 * - protocol catalog view;
 * - selected protocol profile id;
 * - plan readiness report;
 * - requirement report;
 * - participant capability report;
 * - binding composition report;
 * - safe-point/admission evidence;
 * - diagnostics setup profile.
 *
 * The current shape keeps the first admission decision explicit and bounded.
 */

namespace assembler::communication_context
{
    struct TAsccProtocolAdmissionPolicy final
    {
        template <std::size_t CatalogCapacity>
        [[nodiscard]] static constexpr TAsccProtocolReadinessView admit(
            const TAsccProtocolCatalogView<CatalogCapacity>& catalog,
            TBridgeProtocolKind selected_protocol,
            TProtocolRequirementReport requirement_report,
            bool plan_valid,
            bool binding_compatible,
            bool participant_capabilities_satisfied,
            std::string_view note = {}) noexcept
        {
            const bool known = catalog.supports(selected_protocol);

            return TAsccProtocolReadinessView::from_requirement_report(
                selected_protocol,
                requirement_report,
                known,
                plan_valid,
                binding_compatible,
                participant_capabilities_satisfied,
                note);
        }
    };
}

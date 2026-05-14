#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementReport.hpp"

/**
 * @file TAsccProtocolReadinessView.hpp
 * @brief Managerial facade readiness projection for a selected ASCC protocol.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccProtocolReadinessView` is part of the ASCC Managerial Facade. It
 * projects whether a selected protocol family is ready to be admitted into an
 * ASCC component profile after checking protocol requirements, binding
 * compatibility, participant capability satisfaction, and plan alignment.
 *
 * This view is intentionally a readiness/evidence object. It is not a protocol
 * executor, not a bridge executor, and not a policy executor.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * Managerial surface answers:
 *
 * ```text
 * Is the selected ASCC protocol ready for this configured component profile?
 * ```
 *
 * It is used after administrative protocol discovery and before consuming
 * operation.
 *
 * @section relationship_to_protocol_requirements Relationship To Protocol Requirements
 * This view consumes the evidence shape of `TProtocolRequirementReport` from
 * `protocols/requirements/`.
 *
 * `TProtocolRequirementReport` states whether the selected protocol's declared
 * participant, carrier, and binding requirements are satisfied. This readiness
 * view turns that protocol-specific report into facade-level readiness evidence
 * that can contribute to `TAsccManagerialReadinessView` and component
 * admission.
 *
 * Expected relationship:
 *
 * ```text
 * TProtocolRequirementSet
 *     -> TProtocolRequirementMatcher      (future)
 *     -> TProtocolRequirementMatchResult
 *     -> TProtocolRequirementReport
 *     -> TAsccProtocolReadinessView
 *     -> TAsccManagerialReadinessView
 * ```
 *
 * @section relationship_to_protocol_runtime Relationship To Protocol Runtime
 * This view is not `TBridgeProtocol` and does not own protocol state. It may
 * reference a selected `TBridgeProtocolKind`, but it does not advance
 * `TBridgeProtocol`, mutate a `TSession`, or apply `TBridgeTransition`.
 *
 * Runtime entities such as `TBridgeProtocol`, `TBridgeProtocolPlan`,
 * `TBridgeProtocolFrame`, and `TBridgeProtocolResult` remain in the protocol
 * model layer. This view is only a facade-level readiness projection over the
 * selected protocol family.
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * Administrative protocol catalog answers whether the protocol is known.
 * This readiness view answers whether the known protocol is currently ready.
 * Consuming facade may operate only if managerial readiness admits the selected
 * profile.
 *
 * ```text
 * TAsccProtocolCatalogView
 *     -> TAsccProtocolAdmissionPolicy
 *     -> TAsccProtocolReadinessView
 *     -> TAsccConsumingFacade
 * ```
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may require a protocol to be present, forbidden, or
 * selected under certain conditions. This view provides the evidence needed by
 * the Pipeline Composer or composition-level policy assigner to accept or reject
 * the policy-derived protocol selection.
 *
 * ASCC does not own policy semantics. It reports whether its protocol
 * capabilities and requirements are ready to realize a policy-selected profile.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol state advancement;
 * - bridge step execution;
 * - endpoint invocation;
 * - adapter or port calls;
 * - participant instance resolution;
 * - carrier movement;
 * - policy semantics;
 * - persistence/audit export;
 * - dynamic scheduling or asynchronous runtime.
 *
 * @section mature_shape Final Intended Shape
 * In the final mature design, this view should include or reference:
 *
 * - selected protocol kind;
 * - selected protocol profile id;
 * - requirement report summary;
 * - plan readiness report;
 * - binding readiness result;
 * - participant capability match result;
 * - diagnostic/evidence references;
 * - readiness status and explanatory notes.
 *
 * The current version captures the core bounded readiness fields and keeps the
 * type header-only and static-friendly.
 */

namespace assembler::communication_context
{
    struct TAsccProtocolReadinessView final
    {
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TProtocolRequirementReport requirement_report{};
        bool protocol_known{false};
        bool plan_valid{false};
        bool requirements_satisfied{false};
        bool binding_compatible{false};
        bool participant_capabilities_satisfied{false};
        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol != TBridgeProtocolKind::unknown
                && status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && status == TAsccComponentReadinessStatus::ready
                && protocol_known
                && plan_valid
                && requirements_satisfied
                && binding_compatible
                && participant_capabilities_satisfied
                && requirement_report.passed();
        }

        [[nodiscard]] static constexpr TAsccProtocolReadinessView from_requirement_report(
            TBridgeProtocolKind protocol_kind,
            TProtocolRequirementReport report,
            bool known,
            bool valid_plan,
            bool binding_ok,
            bool participant_caps_ok,
            std::string_view note = {}) noexcept
        {
            const bool requirements_ok = report.passed();
            const bool overall_ready = known
                && valid_plan
                && requirements_ok
                && binding_ok
                && participant_caps_ok;

            return TAsccProtocolReadinessView{
                protocol_kind,
                overall_ready
                    ? TAsccComponentReadinessStatus::ready
                    : TAsccComponentReadinessStatus::blocked,
                report,
                known,
                valid_plan,
                requirements_ok,
                binding_ok,
                participant_caps_ok,
                note
            };
        }
    };
}

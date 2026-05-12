#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/binding_views/TBindingView.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/compatibility/views/TCompatibilityView.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/sessions/status/TSessionStatus.hpp"

/**
 * @file TSessionSnapshot.hpp
 * @brief Immutable bridge-visible session snapshot.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - immutable diagnostic snapshot for session id, binding view,
 *   compatibility view, protocol snapshot, status, correlation, and name;
 * - future bridge between session registries, protocol traces, bridge reports,
 *   and validation tools;
 * - no endpoint internals or mutable lifecycle ownership.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - value object with validity and terminal helpers;
 * - readable session state projection.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - session mutation or protocol stepping.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TSessionSnapshot final
    {
        TSessionId session_id{TSessionId::invalid()};
        TSessionStatus status{TSessionStatus::unknown};
        TBindingView binding{};
        TCompatibilityView compatibility{};
        TBridgeProtocolSnapshot protocol{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return session_id.is_valid()
                && status != TSessionStatus::unknown
                && binding.is_valid()
                && compatibility.binding.is_valid()
                && protocol.is_valid();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_session_status(status);
        }

        [[nodiscard]] constexpr bool is_open() const noexcept
        {
            return is_open_session_status(status);
        }
    };
}

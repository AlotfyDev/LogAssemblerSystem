#pragma once

#include <string_view>

#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/terminal_states/TBridgeTerminalState.hpp"

/**
 * @file TBridgeProtocolStateInvariantReport.hpp
 * @brief Diagnostic report for protocol-state consistency invariants.
 *
 * @section ascc_purpose Purpose
 * `TBridgeProtocolStateInvariantReport` summarizes whether a protocol-state
 * snapshot is internally consistent according to ASCC bridge-visible state
 * invariants.
 *
 * It supports diagnostics, readiness gates, tests, and future compliance
 * surfaces without exposing mutable protocol-state internals.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not mutate state, apply transitions, execute protocol or
 * bridge logic, invoke endpoints, export telemetry, or persist diagnostics.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStateInvariantReport final
    {
        TBridgeProtocolSnapshot snapshot{};
        bool snapshot_valid{false};
        bool terminal_stage_matches_terminal_state{false};
        bool success_has_no_error{false};
        bool failure_has_error_or_failed_result{false};
        bool passed{false};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return snapshot_valid;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_valid() && !passed;
        }

        [[nodiscard]] static constexpr TBridgeProtocolStateInvariantReport from_snapshot(
            TBridgeProtocolSnapshot state_snapshot,
            std::string_view report_note = {}) noexcept
        {
            const bool valid = state_snapshot.is_valid();
            const bool stage_terminal = is_terminal_bridge_stage(state_snapshot.current_stage);
            const bool terminal_state = is_terminal_state(state_snapshot.terminal_state);

            const bool terminal_match = valid && (stage_terminal == terminal_state);

            const bool success_ok = valid
                && (state_snapshot.terminal_state != TBridgeTerminalState::success
                    || !state_snapshot.has_error());

            const bool failure_ok = valid
                && (state_snapshot.terminal_state != TBridgeTerminalState::failed
                    || state_snapshot.has_error());

            const bool all_passed = valid
                && terminal_match
                && success_ok
                && failure_ok;

            return TBridgeProtocolStateInvariantReport{
                state_snapshot,
                valid,
                terminal_match,
                success_ok,
                failure_ok,
                all_passed,
                report_note
            };
        }
    };
}

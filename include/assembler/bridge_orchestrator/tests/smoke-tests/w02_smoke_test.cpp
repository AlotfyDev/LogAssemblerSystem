#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/terminal_states/TBridgeTerminalState.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocol_state/lifecycle/TBridgeProtocolState.hpp"

int main()
{
    using namespace assembler::communication_context;

    constexpr auto token = TCorrelationToken::from_parts(10u, 20u);
    static_assert(token.is_valid(), "token should be valid");

    static_assert(!is_terminal_bridge_stage(TBridgeStage::idle), "idle is not terminal");
    static_assert(is_terminal_bridge_stage(TBridgeStage::terminal_success), "success is terminal");
    static_assert(is_terminal_state(TBridgeTerminalState::success), "success state is terminal");

    constexpr auto transition = TBridgeTransition::make(
        TBridgeStage::idle,
        TBridgeStage::session_opening,
        "start");
    static_assert(transition.is_valid(), "transition should be valid");

    auto state = TBridgeProtocolState::start(token);
    const auto applied = state.apply_transition(transition);
    if (!applied)
    {
        return 1;
    }

    auto snapshot = state.snapshot("envelope_placement");
    if (!snapshot.is_valid())
    {
        return 2;
    }

    state.complete(TBridgeResult::success(token));
    if (!state.is_terminal())
    {
        return 3;
    }

    return 0;
}

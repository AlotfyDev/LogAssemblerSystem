#pragma once
#include "assembler/communication_context/sessions/reports/TSessionLifecycleTransitionReport.hpp"
#include "assembler/communication_context/sessions/runtime/TSessionRuntimeContext.hpp"
#include "assembler/communication_context/sessions/transitions/TSessionLifecycleTransitionMatrix.hpp"

/**
 * @file TSessionLifecycleRuntime.hpp
 * @brief Runtime helper for controlled ASCC session lifecycle operations.
 */
namespace assembler::communication_context {
    struct TSessionLifecycleRuntime final {
        [[nodiscard]] static constexpr TSessionRuntimeContext open(TSessionOpenRequest request, TAsccComponentProfileId profile = TAsccComponentProfileId::invalid()) noexcept {
            const auto session = TSession::open(request);
            return {request, session, profile, session.is_open()};
        }
        [[nodiscard]] static constexpr TSessionLifecycleTransitionReport activate(TSession& session) noexcept {
            const auto before = session.status;
            const bool allowed = TSessionLifecycleTransitionMatrix::can_transition(before, TSessionStatus::active);
            const bool accepted = allowed && session.activate();
            return {before, session.status, session.result(), accepted, accepted ? "session activated" : "session activation rejected"};
        }
    };
}

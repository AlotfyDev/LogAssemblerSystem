#pragma once

#include "TReadSideEngineId.hpp"
#include "profile/TReadSideEngineProfile.hpp"
#include "runtime/TReadSideRuntimeState.hpp"
#include "views/TReadSideEngineView.hpp"
#include "reports/TReadSideEngineReport.hpp"
#include "assembler/circulation_mechanism/runtime_core/TCirculationRuntimeDescriptor.hpp"

/*
    TReadSideCirculationEngine.hpp

    Delivery:
        CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

    Current responsibility:
        Injectable ReadSide/PostBridge circulation subsystem facade.

    Production capabilities:
        - accepts ReadSide engine profile
        - validates no PreBridge runtime dependency
        - initializes lifecycle
        - exposes readiness view
        - emits lifecycle reports
        - provides stable injection surface for later ReadSide runtime list waves

    Explicit non-ownership:
        - Does not instantiate PreBridge engine.
        - Does not own Bridge Orchestrator internals.
        - Does not implement receiver/addon behavior.
        - Does not perform persistence or telemetry export.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

class TReadSideCirculationEngine final {
public:
    constexpr TReadSideCirculationEngine() noexcept = default;

    constexpr TReadSideCirculationEngine(TReadSideEngineId id, TReadSideEngineProfile profile) noexcept
        : id_(id), profile_(profile) {
        state_ = (id_.is_valid() && profile_.is_valid()) ? TReadSideRuntimeState::configured : TReadSideRuntimeState::faulted;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && profile_.is_valid();
    }

    [[nodiscard]] constexpr TReadSideEngineView view() const noexcept {
        return TReadSideEngineView{id_, state_, TCirculationRuntimeView{runtime_descriptor()}};
    }

    constexpr TReadSideEngineReport initialize(TReadSideEngineReportId report_id) noexcept {
        const auto before = state_;
        if (!is_valid()) {
            state_ = TReadSideRuntimeState::faulted;
            return TReadSideEngineReport{report_id, id_, before, state_, TReadSideEngineIssueKind::invalid_configuration};
        }
        state_ = TReadSideRuntimeState::ready;
        return TReadSideEngineReport{report_id, id_, before, state_, TReadSideEngineIssueKind::none};
    }

    constexpr TReadSideEngineReport start(TReadSideEngineReportId report_id) noexcept {
        const auto before = state_;
        if (state_ != TReadSideRuntimeState::ready) {
            return TReadSideEngineReport{report_id, id_, before, state_, TReadSideEngineIssueKind::runtime_not_initialized};
        }
        state_ = TReadSideRuntimeState::running;
        return TReadSideEngineReport{report_id, id_, before, state_, TReadSideEngineIssueKind::none};
    }

    constexpr TReadSideEngineReport stop(TReadSideEngineReportId report_id) noexcept {
        const auto before = state_;
        state_ = TReadSideRuntimeState::stopped;
        return TReadSideEngineReport{report_id, id_, before, state_, TReadSideEngineIssueKind::none};
    }

private:
    [[nodiscard]] constexpr TCirculationRuntimeDescriptor runtime_descriptor() const noexcept {
        return TCirculationRuntimeDescriptor{
            TCirculationRuntimeId::from_raw(id_.raw()),
            profile_.config.runtime_configuration,
            state_ == TReadSideRuntimeState::running
                ? TCirculationLifecycleStatus::running
                : (state_ == TReadSideRuntimeState::ready ? TCirculationLifecycleStatus::initialized : TCirculationLifecycleStatus::configured)
        };
    }

    TReadSideEngineId id_{TReadSideEngineId::invalid()};
    TReadSideEngineProfile profile_{};
    TReadSideRuntimeState state_{TReadSideRuntimeState::unconfigured};
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

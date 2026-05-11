#pragma once
#include "TPreBridgeEngineId.hpp"
#include "profile/TPreBridgeCirculationProfile.hpp"
#include "runtime/TPreBridgeRuntimeState.hpp"
#include "views/TPreBridgeEngineView.hpp"
#include "reports/TPreBridgeEngineReport.hpp"
#include "assembler/circulation_mechanism/runtime_core/TCirculationRuntimeDescriptor.hpp"
#include "assembler/circulation_mechanism/runtime_core/lifecycle/TCirculationLifecycleTransition.hpp"

/*
    TPreBridgeCirculationEngine.hpp

    Delivery:
        CME-PREBRIDGE-PROD-W01 — PreBridge Engine Facade And Injection Surface

    Current responsibility:
        Injectable PreBridge subsystem facade.

    Production capabilities:
        - accepts PreBridge profile,
        - validates no ReadSide runtime dependency,
        - initializes lifecycle,
        - exposes readiness view,
        - emits lifecycle reports,
        - provides stable injection surface for future profile/config waves.

    Explicit non-ownership:
        - Does not instantiate ReadSide engine.
        - Does not own receiver lifecycle.
        - Does not execute bridge protocol.
        - Does not replace underlying components.
*/
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

class TPreBridgeCirculationEngine final {
public:
    constexpr TPreBridgeCirculationEngine() noexcept = default;

    constexpr TPreBridgeCirculationEngine(TPreBridgeEngineId id, TPreBridgeCirculationProfile profile) noexcept
        : id_(id), profile_(profile) {
        state_ = (id_.is_valid() && profile_.is_valid()) ? TPreBridgeRuntimeState::configured : TPreBridgeRuntimeState::faulted;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && profile_.is_valid();
    }

    [[nodiscard]] constexpr TPreBridgeEngineView view() const noexcept {
        return TPreBridgeEngineView{id_, state_, TCirculationRuntimeView{runtime_descriptor()}};
    }

    constexpr TPreBridgeEngineReport initialize(TPreBridgeEngineReportId report_id) noexcept {
        const auto before = state_;
        if (!is_valid()) {
            state_ = TPreBridgeRuntimeState::faulted;
            return TPreBridgeEngineReport{report_id, id_, before, state_, TPreBridgeEngineIssueKind::invalid_configuration};
        }
        state_ = TPreBridgeRuntimeState::ready;
        return TPreBridgeEngineReport{report_id, id_, before, state_, TPreBridgeEngineIssueKind::none};
    }

    constexpr TPreBridgeEngineReport start(TPreBridgeEngineReportId report_id) noexcept {
        const auto before = state_;
        if (state_ != TPreBridgeRuntimeState::ready) {
            return TPreBridgeEngineReport{report_id, id_, before, state_, TPreBridgeEngineIssueKind::runtime_not_initialized};
        }
        state_ = TPreBridgeRuntimeState::running;
        return TPreBridgeEngineReport{report_id, id_, before, state_, TPreBridgeEngineIssueKind::none};
    }

    constexpr TPreBridgeEngineReport stop(TPreBridgeEngineReportId report_id) noexcept {
        const auto before = state_;
        state_ = TPreBridgeRuntimeState::stopped;
        return TPreBridgeEngineReport{report_id, id_, before, state_, TPreBridgeEngineIssueKind::none};
    }

private:
    [[nodiscard]] constexpr TCirculationRuntimeDescriptor runtime_descriptor() const noexcept {
        return TCirculationRuntimeDescriptor{
            TCirculationRuntimeId::from_raw(id_.raw()),
            profile_.config.runtime_configuration,
            state_ == TPreBridgeRuntimeState::running
                ? TCirculationLifecycleStatus::running
                : (state_ == TPreBridgeRuntimeState::ready ? TCirculationLifecycleStatus::initialized : TCirculationLifecycleStatus::configured)
        };
    }

    TPreBridgeEngineId id_{TPreBridgeEngineId::invalid()};
    TPreBridgeCirculationProfile profile_{};
    TPreBridgeRuntimeState state_{TPreBridgeRuntimeState::unconfigured};
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

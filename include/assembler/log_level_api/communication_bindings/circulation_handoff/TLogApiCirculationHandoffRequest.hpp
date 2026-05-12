#pragma once

/*
    LOGAPI-W25 — Circulation Handoff Contract

    Responsibility:
        Define the handoff contract from Log Level API envelope exposure toward
        the future circulation intake/admission surface.

    Boundary:
        This wave defines request/result/admission contract carriers only.
        It does not implement circulation engine behavior, placement, slots,
        queues, waiting lists, bridge orchestration, protocol execution, envelope
        assembly, validators, timestamp stabilization, metadata injection, or
        policy assignment.

    Doctrine:
        Log Level API exposes a ready envelope.
        Circulation owns admission and placement.
        This contract bridges readiness to future circulation intake without
        leaking circulation internals into Log Level API.
*/

#include "assembler/log_level_api/envelope/readiness_exposure/TLogApiEnvelopeExposureView.hpp"

#include "TLogApiCirculationAdmissionExpectationKind.hpp"
#include "TLogApiCirculationHandoffId.hpp"
#include "TLogApiCirculationHandoffStatus.hpp"
#include "TLogApiCirculationTargetDescriptor.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

/*
    Contract request from Log Level API to circulation.

    It carries an envelope exposure view, not circulation internals.
*/
struct TLogApiCirculationHandoffRequest final {
    TLogApiCirculationHandoffId id{};
    TLogApiCirculationHandoffStatus status{TLogApiCirculationHandoffStatus::Unknown};
    TLogApiCirculationAdmissionExpectationKind expectation{
        TLogApiCirculationAdmissionExpectationKind::Unknown
    };

    assembler::log_level_api::envelope::readiness_exposure::TLogApiEnvelopeExposureView envelope_exposure{};
    TLogApiCirculationTargetDescriptor target{};

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && (status == TLogApiCirculationHandoffStatus::Ready
                || status == TLogApiCirculationHandoffStatus::SubmittedToContract)
            && expectation != TLogApiCirculationAdmissionExpectationKind::Unknown
            && envelope_exposure.IsReadyForBindingExposure()
            && target.IsResolved()
            && target.accepted_material_kind == "logapi.final_envelope";
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff

#pragma once

/*
    LOGAPI-W24 — Envelope Readiness And Exposure View

    Responsibility:
        Define envelope readiness and exposure view/report types on top of the
        final envelope shape from LOGAPI-W23.

    Boundary:
        This wave does not assemble envelopes, mutate envelopes, perform
        circulation handoff, run validators, execute policy decisions, or persist
        envelope material.

    Doctrine:
        Readiness/exposure views are observational surfaces.
        They help later communication bindings and circulation integration decide
        whether an envelope is visible/ready, without owning downstream behavior.
*/

#include <string>

#include "assembler/log_level_api/envelope/final_shape/TLogApiEnvelopeReadinessView.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelope.hpp"

#include "TLogApiEnvelopeExposureId.hpp"
#include "TLogApiEnvelopeExposureKind.hpp"
#include "TLogApiEnvelopeExposureStatus.hpp"
#include "TLogApiEnvelopeSlotReadiness.hpp"
#include "TLogApiEnvelopeValidationExposureView.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

struct TLogApiEnvelopeExposureView final {
    TLogApiEnvelopeExposureId exposure_id{};
    TLogApiEnvelopeExposureKind exposure_kind{TLogApiEnvelopeExposureKind::Unknown};
    TLogApiEnvelopeExposureStatus status{TLogApiEnvelopeExposureStatus::Unknown};

    std::string envelope_id{};
    std::string envelope_version{};
    std::string envelope_profile_name{};
    std::string content_profile_name{};
    std::string metadata_profile_name{};
    std::string timestamp_profile_name{};

    TLogApiEnvelopeSlotReadiness slot_readiness{};
    TLogApiEnvelopeValidationExposureView validation_view{};

    [[nodiscard]] bool IsReadyForBindingExposure() const noexcept {
        return exposure_id.IsValid()
            && exposure_kind != TLogApiEnvelopeExposureKind::Unknown
            && status == TLogApiEnvelopeExposureStatus::ReadyForBindingExposure
            && slot_readiness.AllSlotsWellFormed();
    }

    [[nodiscard]] static TLogApiEnvelopeExposureView FromEnvelope(
        TLogApiEnvelopeExposureId exposure_id,
        TLogApiEnvelopeExposureKind kind,
        const assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelope& envelope
    ) {
        TLogApiEnvelopeExposureView view{};
        view.exposure_id = exposure_id;
        view.exposure_kind = kind;
        view.envelope_id = envelope.header.id.ToString();
        view.envelope_version = envelope.header.version.ToString();
        view.envelope_profile_name = envelope.header.envelope_profile_name;
        view.content_profile_name = envelope.header.content_profile_name;
        view.metadata_profile_name = envelope.header.metadata_profile_name;
        view.timestamp_profile_name = envelope.header.timestamp_profile_name;
        view.slot_readiness = TLogApiEnvelopeSlotReadiness::From(envelope);
        view.validation_view = TLogApiEnvelopeValidationExposureView::From(envelope.validation_slot);

        view.status = envelope.IsWellShaped()
            ? TLogApiEnvelopeExposureStatus::ReadyForBindingExposure
            : TLogApiEnvelopeExposureStatus::NotReady;

        return view;
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure

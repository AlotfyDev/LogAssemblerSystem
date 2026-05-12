#pragma once

/*
    LOGAPI-W28 — Diagnostics And Failure Model

    Responsibility:
        Define Log Level API diagnostics, failure classification, diagnostic
        records, diagnostic reports, and boundary-local failure ownership across
        configuration, content, parser, metadata, timestamp, envelope, handoff,
        and public API surfaces.

    Boundary:
        This wave does not implement a logging backend, telemetry exporter,
        persistence, recovery engine, policy assignment, circulation engine,
        bridge orchestration, or final receiver behavior.

    Doctrine:
        Diagnostics explain Log Level API-owned states and failures.
        Diagnostics must not become telemetry, database audit, receiver retry,
        or policy governance.
*/

#include "TLogApiDiagnosticCategory.hpp"
#include "TLogApiFailureBoundaryKind.hpp"
#include "TLogApiFailureKind.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiFailureClassification final {
    TLogApiDiagnosticCategory category{TLogApiDiagnosticCategory::Unknown};
    TLogApiFailureBoundaryKind boundary{TLogApiFailureBoundaryKind::Unknown};
};

class TLogApiFailureClassifier final {
public:
    [[nodiscard]] static TLogApiFailureClassification Classify(TLogApiFailureKind kind) noexcept {
        switch (kind) {
            case TLogApiFailureKind::ConfigurationNotReady:
                return {TLogApiDiagnosticCategory::Configuration, TLogApiFailureBoundaryKind::ConfigurationSurface};

            case TLogApiFailureKind::ContentMissing:
                return {TLogApiDiagnosticCategory::ContentInput, TLogApiFailureBoundaryKind::UpstreamCallerInput};

            case TLogApiFailureKind::ParserBindingMissing:
            case TLogApiFailureKind::ParseFailed:
                return {TLogApiDiagnosticCategory::Parser, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::ValidationInvalid:
                return {TLogApiDiagnosticCategory::Validator, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::MetadataProfileMissing:
            case TLogApiFailureKind::MetadataBlockNotReady:
                return {TLogApiDiagnosticCategory::Metadata, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::TimestampConfigNotReady:
            case TLogApiFailureKind::TimestampCalibrationFailed:
                return {TLogApiDiagnosticCategory::Timestamp, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::EnvelopeIncomplete:
                return {TLogApiDiagnosticCategory::Envelope, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::EnvelopeExposureNotReady:
                return {TLogApiDiagnosticCategory::EnvelopeExposure, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::HandoffContractRejected:
                return {TLogApiDiagnosticCategory::CirculationHandoff, TLogApiFailureBoundaryKind::CirculationBoundary};

            case TLogApiFailureKind::PublicApiRejected:
                return {TLogApiDiagnosticCategory::PublicApi, TLogApiFailureBoundaryKind::LogApiOwned};

            case TLogApiFailureKind::IntegrationSmokeRejected:
                return {TLogApiDiagnosticCategory::IntegrationSmoke, TLogApiFailureBoundaryKind::LogApiOwned};

            default:
                return {};
        }
    }
};

} // namespace assembler::log_level_api::diagnostics

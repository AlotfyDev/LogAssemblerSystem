#include "assembler/communication_context/composability/readiness/TAsccReadinessSurface.hpp"

int main()
{
    using namespace assembler::communication_context;

    static_assert(ASCC_COMP_W06_READINESS_SURFACE_AVAILABLE,
                  "W06 readiness surface must be available");

    const auto participant_ready = TAsccParticipantReadinessView::make(
        TAsccReadinessStatus::ready,
        true,
        true,
        true,
        true,
        0u,
        "content_provider_participant_readiness");

    if (!participant_ready.is_valid()) return 1;
    if (!participant_ready.ready()) return 2;

    const auto participant_not_ready = TAsccParticipantReadinessView::make(
        TAsccReadinessStatus::not_ready,
        true,
        true,
        false,
        true,
        1u,
        "missing_participant_capability_readiness");

    if (!participant_not_ready.blocked()) return 3;

    const auto binding_ready = TAsccBindingReadinessView::make(
        TAsccReadinessStatus::ready,
        true,
        true,
        true,
        true,
        true,
        "bridge_mediated_binding_readiness");

    const auto protocol_ready = TAsccProtocolReadinessView::make(
        TAsccReadinessStatus::ready,
        true,
        true,
        true,
        true,
        0u,
        "envelope_placement_protocol_readiness");

    const auto session_ready = TAsccSessionReadinessView::make(
        TAsccReadinessStatus::ready,
        true,
        true,
        true,
        "required_session_readiness");

    const auto bridge_ready = TAsccBridgeReadinessView::make(
        TAsccReadinessStatus::ready,
        true,
        true,
        true,
        true,
        "required_bridge_readiness");

    if (!binding_ready.ready()) return 4;
    if (!protocol_ready.ready()) return 5;
    if (!session_ready.ready()) return 6;
    if (!bridge_ready.ready()) return 7;

    const auto composition_ready = TAsccCompositionReadinessView::make(
        participant_ready,
        binding_ready,
        protocol_ready,
        session_ready,
        bridge_ready,
        TAsccReadinessStatus::ready,
        "ascc_core_composition_readiness");

    if (!composition_ready.is_valid()) return 8;
    if (!composition_ready.ready()) return 9;

    auto report = TAsccReadinessReport<8, 8>::make(
        TAsccReadinessStatus::ready,
        "ascc_w06_smoke_readiness_report");

    if (!report.add_evidence(TAsccReadinessEvidenceRef::make(
            1u,
            TAsccEvidenceDimension::participant_capabilities_satisfied,
            TAsccReadinessStatus::ready,
            "TAsccParticipantReadinessView",
            "ASCC-COMP-W06"))) return 10;

    if (!report.add_evidence(TAsccReadinessEvidenceRef::make(
            2u,
            TAsccEvidenceDimension::composition_metadata_valid,
            TAsccReadinessStatus::ready,
            "TAsccBindingReadinessView",
            "ASCC-COMP-W06"))) return 11;

    if (!report.add_evidence(TAsccReadinessEvidenceRef::make(
            3u,
            TAsccEvidenceDimension::protocol_requirements_satisfied,
            TAsccReadinessStatus::ready,
            "TAsccProtocolReadinessView",
            "ASCC-COMP-W06"))) return 12;

    if (!report.add_issue(TAsccReadinessIssue::make(
            1u,
            TAsccEvidenceDimension::diagnostics_available,
            TAsccReadinessStatus::deferred,
            "diagnostics_surface",
            false,
            "diagnostics evidence deferred"))) return 13;

    if (!report.is_valid()) return 14;
    if (report.ready_evidence_count() != 3u) return 15;
    if (report.deferred_issue_count() != 1u) return 16;
    if (report.blocking_issue_count() != 0u) return 17;
    if (!report.passed_for_core()) return 18;

    auto not_ready_report = TAsccReadinessReport<4, 4>::make(
        TAsccReadinessStatus::ready,
        "ascc_w06_not_ready_report");

    if (!not_ready_report.add_issue(TAsccReadinessIssue::make(
            2u,
            TAsccEvidenceDimension::protocol_requirements_satisfied,
            TAsccReadinessStatus::not_ready,
            "protocol_requirements",
            true,
            "required protocol evidence missing"))) return 19;

    if (!not_ready_report.failed_for_core()) return 20;

    return 0;
}

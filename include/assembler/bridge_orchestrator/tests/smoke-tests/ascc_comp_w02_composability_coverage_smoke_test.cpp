#include "assembler/communication_context/composability/TAsccComposabilitySurface.hpp"

int main()
{
    using namespace assembler::communication_context;

    static_assert(ASCC_COMP_W02_COMPOSABILITY_SURFACE_AVAILABLE,
                  "W02 composability surface must be available");

    auto capabilities = TAsccComposableCapabilitySet<8>::make("w02_capabilities");

    const bool added_participant = capabilities.add(
        TAsccComposableCapability::make(
            TAsccComposableCapabilityId::from_value(1u),
            TAsccComposableCapabilityKind::participant_identity,
            "participants",
            "participant identity is covered"));

    const bool added_registry = capabilities.add(
        TAsccComposableCapability::make(
            TAsccComposableCapabilityId::from_value(2u),
            TAsccComposableCapabilityKind::registry_catalog,
            "registries",
            "registry catalog is covered"));

    if (!added_participant || !added_registry)
    {
        return 1;
    }

    if (!capabilities.contains(TAsccComposableCapabilityKind::participant_identity))
    {
        return 2;
    }

    auto requirements = TAsccRequirementSet<8>::make("w02_requirements");

    if (!requirements.add(TAsccRequirement::make(
            1u,
            TAsccRequirementKind::requires_participant_identity,
            "pipeline_composer",
            "composer requires participant identity")))
    {
        return 3;
    }

    if (!requirements.add(TAsccRequirement::make(
            2u,
            TAsccRequirementKind::requires_integration_boundary,
            "integration_pack",
            "integration boundary is deferred")))
    {
        return 4;
    }

    if (requirements.core_count() != 1u)
    {
        return 5;
    }

    auto coverage = TAsccCoverageMatrix<8>::make("w02_coverage");

    if (!coverage.add(TAsccCoverageItem::make(
            1u,
            TAsccRequirementKind::requires_participant_identity,
            TAsccComposableCapabilityKind::participant_identity,
            TAsccCoverageState::covered,
            "participants",
            "ASCC-COMP-W01")))
    {
        return 6;
    }

    if (!coverage.add(TAsccCoverageItem::make(
            2u,
            TAsccRequirementKind::requires_integration_boundary,
            TAsccComposableCapabilityKind::integration_boundary_surface,
            TAsccCoverageState::deferred_to_integration,
            "integration_boundaries",
            "ASCC-INT")))
    {
        return 7;
    }

    if (coverage.covered_count() != 1u)
    {
        return 8;
    }

    if (coverage.deferred_count() != 1u)
    {
        return 9;
    }

    if (coverage.has_blocking_core_items())
    {
        return 10;
    }

    const auto report = TAsccComposabilityReport::from_matrix(coverage, "w02_report");

    if (!report.passed_for_core())
    {
        return 11;
    }

    const auto missing_core = TAsccCoverageItem::make(
        3u,
        TAsccRequirementKind::requires_readiness_surface,
        TAsccComposableCapabilityKind::readiness_evidence,
        TAsccCoverageState::missing,
        "readiness",
        "ASCC-COMP-W06");

    auto gap_report = TAsccCoverageGapReport<4>::make("w02_gap_report");
    const auto derived_gap = TAsccCoverageGap::from_coverage(
        1u,
        missing_core,
        TAsccComposabilitySeverity::blocking,
        "missing core readiness evidence");

    if (!gap_report.add(derived_gap))
    {
        return 12;
    }

    if (!gap_report.blocks_core_readiness())
    {
        return 13;
    }

    return 0;
}

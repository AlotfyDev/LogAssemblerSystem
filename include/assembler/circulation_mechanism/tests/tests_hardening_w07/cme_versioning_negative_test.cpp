#include "assembler/circulation_mechanism/circulation_mechanism_versioning.hpp"
using namespace assembler::circulation_mechanism::versioning;

int main() {
    constexpr TCirculationVersionSet too_new{TCirculationApiVersion::from_raw(3), TCirculationProfileVersion::from_raw(1), TCirculationSchemaVersion::from_raw(1)};
    constexpr TCirculationVersionSet supported{TCirculationApiVersion::from_raw(2), TCirculationProfileVersion::from_raw(2), TCirculationSchemaVersion::from_raw(2)};
    constexpr TCirculationFeatureFlagSet flags{};
    constexpr auto report = TCirculationCompatibilityPolicy::evaluate(TCirculationCompatibilityReportId::from_raw(1), too_new, supported, flags);
    static_assert(!report.compatible(), "newer API is incompatible");
    static_assert(report.issue == TCirculationVersionIssueKind::api_version_too_new, "api too new");

    constexpr TCirculationFeatureFlagSet blocked{
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::pre_bridge_engine, TCirculationFeatureFlagState::blocked},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::read_side_engine, TCirculationFeatureFlagState::enabled},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::diagnostics_export, TCirculationFeatureFlagState::enabled},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::adapter_contracts, TCirculationFeatureFlagState::enabled},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::performance_benchmarks, TCirculationFeatureFlagState::enabled},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::concurrency_policy, TCirculationFeatureFlagState::enabled},
        TCirculationFeatureFlag{TCirculationFeatureFlagKind::legacy_compatibility_layer, TCirculationFeatureFlagState::deprecated}
    };
    constexpr TCirculationVersionSet ok{TCirculationApiVersion::from_raw(1), TCirculationProfileVersion::from_raw(1), TCirculationSchemaVersion::from_raw(1)};
    constexpr auto blocked_report = TCirculationCompatibilityPolicy::evaluate(TCirculationCompatibilityReportId::from_raw(2), ok, supported, blocked);
    static_assert(!blocked_report.compatible(), "blocked feature set is incompatible");
    static_assert(blocked_report.issue == TCirculationVersionIssueKind::feature_flag_required, "feature flag required");
    return 0;
}

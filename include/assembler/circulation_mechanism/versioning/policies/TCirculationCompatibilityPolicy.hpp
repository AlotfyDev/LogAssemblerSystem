#pragma once
#include "../reports/TCirculationCompatibilityReport.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationCompatibilityPolicy final {
    [[nodiscard]] static constexpr TCirculationCompatibilityReport evaluate(TCirculationCompatibilityReportId report_id, TCirculationVersionSet requested, TCirculationVersionSet supported, TCirculationFeatureFlagSet features) noexcept {
        if (!requested.api_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::incompatible, TCirculationVersionIssueKind::invalid_requested_api_version};
        if (!supported.api_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::blocked, TCirculationVersionIssueKind::invalid_supported_api_version};
        if (!requested.profile_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::incompatible, TCirculationVersionIssueKind::invalid_requested_profile_version};
        if (!supported.profile_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::blocked, TCirculationVersionIssueKind::invalid_supported_profile_version};
        if (!requested.schema_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::incompatible, TCirculationVersionIssueKind::invalid_requested_schema_version};
        if (!supported.schema_version.is_valid()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::blocked, TCirculationVersionIssueKind::invalid_supported_schema_version};
        if (requested.api_version.raw() > supported.api_version.raw()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::incompatible, TCirculationVersionIssueKind::api_version_too_new};
        if (requested.profile_version.raw() > supported.profile_version.raw()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::requires_migration, TCirculationVersionIssueKind::profile_version_too_new};
        if (requested.schema_version.raw() > supported.schema_version.raw()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::requires_migration, TCirculationVersionIssueKind::schema_version_too_new};
        if (!features.required_production_features_enabled()) return {report_id, requested, supported, features, TCirculationCompatibilityStatus::blocked, TCirculationVersionIssueKind::feature_flag_required};
        return {report_id, requested, supported, features, features.uses_deprecated_legacy_compatibility() ? TCirculationCompatibilityStatus::compatible_with_deprecation : TCirculationCompatibilityStatus::compatible, TCirculationVersionIssueKind::none};
    }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

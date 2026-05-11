#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

enum class TCirculationVersionIssueKind : std::uint8_t { none, invalid_requested_api_version, invalid_supported_api_version, invalid_requested_profile_version, invalid_supported_profile_version, invalid_requested_schema_version, invalid_supported_schema_version, api_version_too_new, profile_version_too_new, schema_version_too_new, feature_flag_required, deprecated_feature_used, blocked_feature_used };
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

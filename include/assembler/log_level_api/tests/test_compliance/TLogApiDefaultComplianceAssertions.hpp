#pragma once

/*
    LOGAPI-W29 — Test Compliance Suite

    Responsibility:
        Define Log Level API compliance assertions, test case descriptors,
        compliance dimensions/outcomes/severity, negative compliance catalog,
        compliance suite report, and production-hardening test readiness views.

    Boundary:
        This wave defines test/compliance descriptors only.
        It does not implement CI, a test runner, logging backend, telemetry,
        persistence, recovery, policy assignment, circulation engine, bridge
        orchestration, or receiver behavior.

    Doctrine:
        Compliance proves boundary discipline:
        configure first, consume content only, no per-call config, no premature
        policy assignment, no circulation internals, no bridge orchestration.
*/

#include <vector>

#include "TLogApiComplianceAssertion.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiDefaultComplianceAssertions final {
    [[nodiscard]] static std::vector<TLogApiComplianceAssertion> Make() {
        return {
            {TLogApiComplianceAssertionId{1}, TLogApiComplianceDimension::ConfigurationFirst, TLogApiComplianceSeverity::Fatal,
             "configuration_first", "Configuration must be resolved before consuming content.", true},

            {TLogApiComplianceAssertionId{2}, TLogApiComplianceDimension::ContentOnlyPublicApi, TLogApiComplianceSeverity::Fatal,
             "content_only_public_api", "Public API calls must carry content only and no per-call schema/metadata/validator/timestamp/policy material.", true},

            {TLogApiComplianceAssertionId{3}, TLogApiComplianceDimension::ParserBinding, TLogApiComplianceSeverity::Error,
             "parser_binding_configuration_time", "Parser binding must be resolved during configuration and not discovered in the hot path.", true},

            {TLogApiComplianceAssertionId{4}, TLogApiComplianceDimension::MetadataSeparation, TLogApiComplianceSeverity::Error,
             "metadata_not_content", "Metadata must remain separate from content schemas and payloads.", true},

            {TLogApiComplianceAssertionId{5}, TLogApiComplianceDimension::TimestampSeparation, TLogApiComplianceSeverity::Error,
             "timestamp_not_metadata_or_content", "Stabilized timestamp must remain separate from content and metadata.", true},

            {TLogApiComplianceAssertionId{6}, TLogApiComplianceDimension::EnvelopeShape, TLogApiComplianceSeverity::Fatal,
             "envelope_has_required_slots", "Final envelope must expose content, metadata, timestamp, and validation result slots.", true},

            {TLogApiComplianceAssertionId{7}, TLogApiComplianceDimension::CirculationBoundary, TLogApiComplianceSeverity::Fatal,
             "no_circulation_internals", "Log Level API must not own circulation placement, slots, queues, waiting lists, or dispatcher internals.", true},

            {TLogApiComplianceAssertionId{8}, TLogApiComplianceDimension::PolicyDeferred, TLogApiComplianceSeverity::Info,
             "policy_assignment_deferred", "Policy assignment remains deferred until governable functional-object behavior exists.", false}
        };
    }
};

} // namespace assembler::log_level_api::test_compliance

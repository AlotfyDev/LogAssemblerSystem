#pragma once

/*
    LOGAPI-W22 — Timestamp Stabilization Policies Optional

    Responsibility:
        Define optional policy-sensitive timestamp stabilization descriptors,
        timestamp stabilization rule profiles, change/switch requests, readiness
        reports, and policy-reference carriers.

    Boundary:
        This wave does not implement ecosystem governance, policy assignment,
        TPolicyObjectHost, realizer behavior, clock acquisition, calendar conversion,
        envelope assembly, circulation handoff, or persistence.

    Doctrine:
        Timestamp stabilization can run as configuration.
        Changing timestamp semantics may be policy-sensitive.
        This wave only models optional governance hooks for timestamp profiles.
*/

#include "TLogApiDefaultTimestampPolicyProfiles.hpp"
#include "TLogApiTimestampOptionalPolicyView.hpp"
#include "TLogApiTimestampPolicyReadinessEvaluator.hpp"
#include "TLogApiTimestampPolicyReadinessIssue.hpp"
#include "TLogApiTimestampPolicyReadinessReport.hpp"
#include "TLogApiTimestampPolicyRef.hpp"
#include "TLogApiTimestampPolicySensitivityKind.hpp"
#include "TLogApiTimestampProfileSwitchDecision.hpp"
#include "TLogApiTimestampProfileSwitchKind.hpp"
#include "TLogApiTimestampProfileSwitchPlanner.hpp"
#include "TLogApiTimestampProfileSwitchRequest.hpp"
#include "TLogApiTimestampProfileSwitchResult.hpp"
#include "TLogApiTimestampSafePointFlag.hpp"
#include "TLogApiTimestampSafePointKind.hpp"
#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"
#include "TLogApiTimestampStabilizationRuleId.hpp"
#include "TLogApiTimestampStabilizationRuleStatus.hpp"

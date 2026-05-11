#pragma once

/*
    circulation_mechanism_w13.hpp

    Convenience include for CME-W13 eviction and time range skeleton.
    This header does not implement eviction execution.
*/

#include "eviction/TEvictionCandidateId.hpp"
#include "eviction/TEvictionPolicyKind.hpp"
#include "eviction/TEvictionCandidateStatus.hpp"
#include "eviction/TTimeRangeCompletenessStatus.hpp"
#include "eviction/TContainerTimeRange.hpp"
#include "eviction/TEvictionCandidate.hpp"
#include "eviction/views/TContainerTimeRangeView.hpp"
#include "eviction/views/TEvictionCandidateView.hpp"

#include "eviction/policies/TEvictionPolicyProfileId.hpp"
#include "eviction/policies/TEvictionPolicyProfile.hpp"
#include "eviction/policies/TOldestTimeRangeEviction.hpp"
#include "eviction/policies/TFifoContainerEviction.hpp"
#include "eviction/policies/TNoEvictionPreBridgeProfile.hpp"
#include "eviction/policies/TDelegateToReadSideProfile.hpp"
#include "eviction/policies/TEmergencyEvictionProfile.hpp"

#include "eviction/reports/TEvictionReportId.hpp"
#include "eviction/reports/TEvictionReportKind.hpp"
#include "eviction/reports/TEvictionSelectionReport.hpp"
#include "eviction/reports/TEvictionAppliedReport.hpp"
#include "eviction/reports/TEvictionRejectedReport.hpp"
#include "eviction/reports/TCapacityDelegatedToReadSideReport.hpp"

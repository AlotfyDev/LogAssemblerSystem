#pragma once
/*
    circulation_mechanism_eviction.hpp
    Delivery: CME-EVICTION-PROD-W01 — Production SafePoint Candidate Contract
*/
#include "eviction/TEvictionCandidateId.hpp"
#include "eviction/TEvictionPolicyKind.hpp"
#include "eviction/TEvictionCandidateStatus.hpp"
#include "eviction/TEvictionEvaluationStatus.hpp"
#include "eviction/TTimeRangeCompletenessStatus.hpp"
#include "container/TContainerTimeRange.hpp"
#include "eviction/TEvictionCandidate.hpp"
#include "container/TContainerTimeRangeView.hpp"
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

#pragma once

/*
    circulation_mechanism_w12.hpp

    Convenience include for CME-W12 safe-point and release/recycle skeleton.
    This header does not implement reset, recycle, or safe-point algorithms.
*/

#include "safe_points/TSafePointId.hpp"
#include "safe_points/TSafePointKind.hpp"
#include "safe_points/TSafePointView.hpp"
#include "safe_points/TSafePointPolicy.hpp"
#include "safe_points/TSafePointViolationReport.hpp"

#include "release_recycle/TReleaseRecycleId.hpp"
#include "release_recycle/TReleaseKind.hpp"
#include "release_recycle/TRecycleState.hpp"
#include "release_recycle/views/TReleaseRecycleView.hpp"
#include "release_recycle/views/TReentryEligibilityView.hpp"
#include "release_recycle/reports/TReleaseRecycleReportId.hpp"
#include "release_recycle/reports/TRecycleReport.hpp"
#include "release_recycle/reports/TResetAppliedReport.hpp"
#include "release_recycle/reports/TExposureReleaseReport.hpp"
#include "release_recycle/policies/TRecyclePolicy.hpp"

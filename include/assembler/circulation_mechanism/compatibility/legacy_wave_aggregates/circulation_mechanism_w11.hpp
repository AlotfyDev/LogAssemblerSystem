#pragma once

/*
    circulation_mechanism_w11.hpp

    Convenience include for CME-W11 Dispatcher and Passive Exposure Skeleton.
    This header does not implement bridge protocol, receiver lifecycle, or copy/move behavior.
*/

#include "dispatcher/TDispatcherId.hpp"
#include "dispatcher/TDispatcherStatus.hpp"
#include "dispatcher/TDispatchExposureStatus.hpp"
#include "dispatcher/profiles/TDispatchProfileKind.hpp"
#include "dispatcher/profiles/TPassivePullDispatchProfile.hpp"
#include "dispatcher/profiles/TPushDispatchProfile.hpp"
#include "dispatcher/boundary/TDispatchBoundaryId.hpp"
#include "dispatcher/boundary/TDispatchBoundaryStatus.hpp"
#include "dispatcher/boundary/TDispatchBoundaryDescriptor.hpp"
#include "dispatcher/views/TDispatchExposureView.hpp"
#include "dispatcher/views/TDispatchReadyView.hpp"
#include "dispatcher/views/TDispatcherView.hpp"
#include "dispatcher/views/TDispatchBoundaryView.hpp"
#include "dispatcher/reports/TDispatchReportId.hpp"
#include "dispatcher/reports/TDispatchExposureReport.hpp"
#include "dispatcher/reports/TPassiveExposureReport.hpp"
#include "dispatcher/reports/TBoundaryAssumptionBrokenReport.hpp"
#include "dispatcher/reports/TPushDispatchAttemptReport.hpp"
#include "dispatcher/TDispatcher.hpp"

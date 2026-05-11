#pragma once

/*
    circulation_mechanism_w07.hpp

    Convenience include for CME-W07 waiting-list and round-manager skeletons.
    This header does not implement reference calculation, ingress placement, or dispatch exposure.
*/

#include "waiting_list/TWaitingListState.hpp"
#include "waiting_list/TWaitingListEntry.hpp"
#include "waiting_list/TIngressWaitingListView.hpp"
#include "waiting_list/TDispatchWaitingListView.hpp"
#include "waiting_list/TIngressWaitingListRegistrationReport.hpp"
#include "waiting_list/TDispatchWaitingListRegistrationReport.hpp"
#include "waiting_list/TIngressWaitingList.hpp"
#include "waiting_list/TDispatchWaitingList.hpp"

#include "round_manager/TRoundKind.hpp"
#include "round_manager/TRoundAdmissionDecisionKind.hpp"
#include "round_manager/TRoundView.hpp"
#include "round_manager/TRoundAdmissionReport.hpp"
#include "round_manager/TRoundClosureReport.hpp"
#include "round_manager/TRoundManager.hpp"

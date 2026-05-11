#pragma once

/*
    circulation_mechanism_state.hpp

    Delivery:
        CME-STATE-PROD-W01 — Production Transition Contract

    Responsibility:
        Aggregate include for production-grade CME state vocabularies and
        transition contract helpers.
*/

#include "state/TBundleAgentState.hpp"
#include "state/TContainerState.hpp"
#include "state/TDispatchExposureState.hpp"
#include "state/TModeratorState.hpp"
#include "state/TReferenceSupplyState.hpp"
#include "state/TReferenceValidityState.hpp"
#include "state/TRoundState.hpp"
#include "state/TSafePointState.hpp"
#include "state/TSlotState.hpp"
#include "state/TStateTransitionIssueKind.hpp"
#include "state/TStateTransitionResult.hpp"
#include "state/TStateTransitionValidator.hpp"

#pragma once

/*
    circulation_mechanism_w01.hpp

    Convenience include for CME-W01 foundational identity and state atoms.
    This header does not create a facade or runtime component.
*/

#include "ids/TContainerId.hpp"
#include "ids/TContainerRegistryIndex.hpp"
#include "ids/TSlotIndex.hpp"
#include "ids/TRoundId.hpp"
#include "ids/TReferenceId.hpp"
#include "ids/TBoundaryId.hpp"

#include "state/TSlotState.hpp"
#include "state/TContainerState.hpp"
#include "state/TRoundState.hpp"
#include "state/TModeratorState.hpp"
#include "state/TBundleAgentState.hpp"
#include "state/TReferenceValidityState.hpp"
#include "state/TReferenceSupplyState.hpp"
#include "state/TSafePointState.hpp"
#include "state/TDispatchExposureState.hpp"

#include "diagnostics/TDiagnosticSeverity.hpp"
#include "diagnostics/TDiagnosticCategory.hpp"

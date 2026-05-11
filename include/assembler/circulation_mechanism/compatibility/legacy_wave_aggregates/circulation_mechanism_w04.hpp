#pragma once

/*
    circulation_mechanism_w04.hpp

    Convenience include for CME-W04 slot and container skeleton.
    This header does not create registry, ingress, dispatch, or reference calculation behavior.
*/

#include "slot/TSlot.hpp"
#include "slot/TSlotView.hpp"
#include "slot/TSlotOccupancyView.hpp"
#include "slot/TSlotTransitionReport.hpp"

#include "container/TContainer.hpp"
#include "container/TContainerView.hpp"
#include "container/TContainerStateView.hpp"
#include "container/TContainerSlotLayoutView.hpp"
#include "container/TContainerTimeRange.hpp"
#include "container/TContainerTimeRangeView.hpp"
#include "container/TContainerStateTransitionReport.hpp"

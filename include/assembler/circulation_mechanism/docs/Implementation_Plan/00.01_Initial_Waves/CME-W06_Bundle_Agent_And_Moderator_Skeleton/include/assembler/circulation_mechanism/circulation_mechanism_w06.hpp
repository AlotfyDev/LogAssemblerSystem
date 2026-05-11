#pragma once

/*
    circulation_mechanism_w06.hpp

    Convenience include for CME-W06 BundleAgent and Moderator skeletons.
    This header does not create scaling execution, reset algorithms, or round membership behavior.
*/

#include "bundle_agent/TBundleAgentId.hpp"
#include "bundle_agent/TContainerFamilyId.hpp"
#include "bundle_agent/TBundleTopologyView.hpp"
#include "bundle_agent/TBundleScalingReport.hpp"
#include "bundle_agent/TDefaultEmptyContainerProfileReport.hpp"
#include "bundle_agent/TSlotsContainerBundleAgentConfig.hpp"
#include "bundle_agent/TSlotsContainerBundleAgent.hpp"

#include "moderator/TModeratorId.hpp"
#include "moderator/TModeratorReadinessView.hpp"
#include "moderator/TModeratedContainerView.hpp"
#include "moderator/TContainerResetReport.hpp"
#include "moderator/TSlotsContainerModeratorConfig.hpp"
#include "moderator/TSlotsContainerModerator.hpp"

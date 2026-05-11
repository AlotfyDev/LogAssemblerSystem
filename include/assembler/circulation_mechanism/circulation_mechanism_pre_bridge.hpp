#pragma once
/*
    circulation_mechanism_pre_bridge.hpp

    Canonical PreBridge subsystem aggregate.
*/
#include "pre_bridge/TPreBridgeEngineId.hpp"
#include "pre_bridge/runtime/TPreBridgeRuntimeState.hpp"
#include "pre_bridge/reports/TPreBridgeEngineIssueKind.hpp"
#include "pre_bridge/config/TPreBridgeCirculationConfig.hpp"
#include "pre_bridge/profile/TPreBridgeCirculationProfile.hpp"
#include "pre_bridge/views/TPreBridgeEngineView.hpp"
#include "pre_bridge/reports/TPreBridgeEngineReport.hpp"
#include "pre_bridge/TPreBridgeCirculationEngine.hpp"
#include "pre_bridge/bindings/TPreBridgeCapacityBinding.hpp"
#include "pre_bridge/bindings/TPreBridgeBoundaryBinding.hpp"
#include "pre_bridge/bindings/TPreBridgeReferenceSupplyBinding.hpp"
#include "pre_bridge/bindings/TPreBridgeDiagnosticsBinding.hpp"
#include "pre_bridge/bindings/TPreBridgeBindingSetId.hpp"
#include "pre_bridge/bindings/TPreBridgeBindingSet.hpp"
#include "pre_bridge/default_profile/TPreBridgeDefaultProfileId.hpp"
#include "pre_bridge/default_profile/TPreBridgeDefaultProfileStatus.hpp"
#include "pre_bridge/default_profile/TPreBridgeDefaultInjectionProfile.hpp"
#include "pre_bridge/views/TPreBridgeDefaultProfileView.hpp"
#include "pre_bridge/reports/TPreBridgeConfigurationIssueKind.hpp"
#include "pre_bridge/reports/TPreBridgeConfigurationReport.hpp"

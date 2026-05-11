#pragma once

/*
    circulation_mechanism_w14.hpp

    Convenience include for CME-W14 communication binding integration skeleton.
    This header does not implement adapter invocation, bridge runtime, or Log API runtime.
*/

#include "communication_bindings/TCommunicationBindingId.hpp"
#include "communication_bindings/TCommunicationBindingStatus.hpp"
#include "communication_bindings/TCommunicationBindingKind.hpp"
#include "communication_bindings/TBindingCompatibilityStatus.hpp"
#include "communication_bindings/TCommunicationBindingCompatibility.hpp"
#include "communication_bindings/TCirculationCommunicationBindingDescriptor.hpp"
#include "communication_bindings/TCommunicationBindingCompatibilityPolicy.hpp"

#include "communication_bindings/ingress/TEnvelopePlacementPortId.hpp"
#include "communication_bindings/ingress/TEnvelopePlacementPortDescriptor.hpp"
#include "communication_bindings/ingress/TIngressBindingView.hpp"

#include "communication_bindings/dispatch_output/TDispatchOutputAdapterId.hpp"
#include "communication_bindings/dispatch_output/TBridgeFacingDispatchAdapterDescriptor.hpp"
#include "communication_bindings/dispatch_output/TDispatchOutputBindingView.hpp"

#include "communication_bindings/views/TCirculationCommunicationBindingView.hpp"

#include "communication_bindings/reports/TCommunicationBindingReportId.hpp"
#include "communication_bindings/reports/TCommunicationBindingIssueKind.hpp"
#include "communication_bindings/reports/TCommunicationBindingReport.hpp"

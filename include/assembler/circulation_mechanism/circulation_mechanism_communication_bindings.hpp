#pragma once
/*
    circulation_mechanism_communication_bindings.hpp
    Delivery: CME-COMMBIND-PROD-W01 — Production Boundary And Exposure Contracts
*/
#include "communication_bindings/TCommunicationBindingId.hpp"
#include "communication_bindings/TCommunicationBindingStatus.hpp"
#include "communication_bindings/TCommunicationBindingKind.hpp"
#include "communication_bindings/TBindingCompatibilityStatus.hpp"
#include "communication_bindings/TCommunicationBindingCompatibility.hpp"
#include "communication_bindings/exposure_contracts/TExposureContractId.hpp"
#include "communication_bindings/exposure_contracts/TExposureMode.hpp"
#include "communication_bindings/exposure_contracts/TExposureMaterialKind.hpp"
#include "communication_bindings/exposure_contracts/TExposureContractDescriptor.hpp"
#include "communication_bindings/ingress/TEnvelopePlacementPortId.hpp"
#include "communication_bindings/ingress/TEnvelopePlacementPortDescriptor.hpp"
#include "communication_bindings/ingress/TIngressBindingView.hpp"
#include "communication_bindings/dispatch_output/TDispatchOutputAdapterId.hpp"
#include "communication_bindings/dispatch_output/TBridgeFacingDispatchAdapterDescriptor.hpp"
#include "communication_bindings/dispatch_output/TDispatchOutputBindingView.hpp"
#include "communication_bindings/bridge_facing_boundary/TBridgeFacingBoundaryId.hpp"
#include "communication_bindings/bridge_facing_boundary/TBridgeFacingBoundaryStatus.hpp"
#include "communication_bindings/bridge_facing_boundary/TBridgeFacingBoundaryDescriptor.hpp"
#include "communication_bindings/TCirculationCommunicationBindingDescriptor.hpp"
#include "communication_bindings/TCommunicationBindingCompatibilityPolicy.hpp"
#include "communication_bindings/reports/TCommunicationBindingReportId.hpp"
#include "communication_bindings/reports/TCommunicationBindingIssueKind.hpp"
#include "communication_bindings/reports/TCommunicationBindingReport.hpp"
#include "communication_bindings/views/TCirculationCommunicationBindingView.hpp"

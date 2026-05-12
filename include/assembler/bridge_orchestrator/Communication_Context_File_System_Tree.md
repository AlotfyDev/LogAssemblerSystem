├───bindings
│   │   TBinding.hpp
│   │
│   ├───adapter_port_bindings
│   ├───binding_policies
│   │       .keep
│   │       TBindingPolicy.hpp
│   │
│   ├───binding_views
│   │       .keep
│   │       TBindingView.hpp
│   │
│   ├───compatibility
│   │       TBindingCompatibilityReport.hpp
│   │
│   ├───concrete_bindings
│   │   ├───log_level_api
│   │   │   └───envelope_plugin_adapter
│   │   │       ├───carriers
│   │   │       │       TLogLevelEnvelopeDescriptor.hpp
│   │   │       │
│   │   │       ├───config
│   │   │       │       TLogLevelAPIEnvelopePluginAdapterConfig.hpp
│   │   │       │
│   │   │       ├───factory
│   │   │       │       TLogLevelAPIEnvelopePluginAdapterFactory.hpp
│   │   │       │
│   │   │       ├───state
│   │   │       │       TLogLevelAPIEnvelopePluginAdapterState.hpp
│   │   │       │
│   │   │       └───views
│   │   │               TLogLevelAPIEnvelopePluginAdapterViewBuilder.hpp
│   │   │
│   │   └───write_side
│   │       ├───envelope_placement_port
│   │       │   │   TWriteSideEnvelopePlacementPortBinding.hpp
│   │       │   │
│   │       │   ├───carriers
│   │       │   │       TWriteSidePlacementTargetDescriptor.hpp
│   │       │   │
│   │       │   ├───config
│   │       │   │       TWriteSideEnvelopePlacementPortConfig.hpp
│   │       │   │
│   │       │   ├───factory
│   │       │   │       TWriteSideEnvelopePlacementPortFactory.hpp
│   │       │   │
│   │       │   ├───policies
│   │       │   │       TWriteSideEnvelopePlacementAdmissionPolicy.hpp
│   │       │   │
│   │       │   ├───state
│   │       │   │       TWriteSideEnvelopePlacementPortState.hpp
│   │       │   │
│   │       │   └───views
│   │       │           TWriteSideEnvelopePlacementPortViewBuilder.hpp
│   │       │
│   │       └───registry_delivery_plugin_adapter
│   │               TWriteSideRegistryDeliveryPluginAdapter.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───ids
│   │       TBindingId.hpp
│   │
│   ├───profiles
│   │       TBindingProfile.hpp
│   │
│   ├───results
│   │       .keep
│   │       TBindingResult.hpp
│   │
│   ├───status
│   │       TBindingStatus.hpp
│   │
│   └───tests
│           .keep
│
├───bridge_carriers
│   ├───admission
│   │       .keep
│   │       TAdmissionResult.hpp
│   │
│   ├───correlation
│   │       .keep
│   │       TCorrelationToken.hpp
│   │
│   ├───destination
│   │       .keep
│   │       TNextDestinationRequest.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───errors
│   │       .keep
│   │       TBridgeCarrierError.hpp
│   │
│   ├───handles
│   │       .keep
│   │       TPlacementHandle.hpp
│   │
│   ├───readiness
│   │       .keep
│   │       TReadinessView.hpp
│   │
│   ├───requests
│   │       .keep
│   │       TPlacementRequest.hpp
│   │
│   ├───results
│   │       .keep
│   │       TBridgeCarrierResult.hpp
│   │
│   ├───signals
│   │       .keep
│   │       TLoadSignal.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   └───views
│           .keep
│           TCarrierView.hpp
│
├───bridge_core
│   │   TBridge.hpp
│   │   TBridgeCore.hpp
│   │
│   ├───budget
│   │       TBridgeStepBudget.hpp
│   │
│   ├───config
│   │       TBridgeConfig.hpp
│   │       TBridgeRunMode.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───errors
│   │       .keep
│   │       TBridgeError.hpp
│   │
│   ├───execution
│   │       .keep
│   │
│   ├───frames
│   │       TBridgeCoreFrame.hpp
│   │
│   ├───ids
│   │       TBridgeId.hpp
│   │
│   ├───issues
│   │       TBridgeCoreIssue.hpp
│   │
│   ├───orchestration
│   │       TBridge.hpp
│   │
│   ├───policies
│   │       TBridgeCorePolicy.hpp
│   │
│   ├───reports
│   │       TBridgeCoreStepReport.hpp
│   │
│   ├───results
│   │       .keep
│   │       TBridgeCoreResult.hpp
│   │       TBridgeResult.hpp
│   │
│   ├───snapshots
│   │       TBridgeCoreSnapshot.hpp
│   │
│   ├───status
│   │       TBridgeStatus.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───traces
│   │       TBridgeCoreTrace.hpp
│   │
│   ├───traits
│   │       .keep
│   │       TBridgeTraits.hpp
│   │
│   └───views
│           TBridgeCoreView.hpp
│
├───channels
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───policies
│   │       .keep
│   │       TChannelBindingPolicy.hpp
│   │
│   ├───profiles
│   │       .keep
│   │       TChannelProfile.hpp
│   │       TSingleAdapterSinglePortProfile.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───topology
│   │       .keep
│   │       TChannel.hpp
│   │
│   └───views
│           .keep
│
├───compatibility
│   │   TCompatibilityEvaluator.hpp
│   │
│   ├───binding_compatibility
│   │       .keep
│   │       TBindingCompatibility.hpp
│   │
│   ├───carrier_compatibility
│   │       .keep
│   │       TCarrierCompatibility.hpp
│   │
│   ├───channel_compatibility
│   │       .keep
│   │       TChannelCompatibility.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───dimensions
│   │       TCompatibilityDimension.hpp
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───issues
│   │       TCompatibilityIssue.hpp
│   │
│   ├───matrix
│   │       TCompatibilityMatrix.hpp
│   │
│   ├───ownership_compatibility
│   │       .keep
│   │       TOwnershipCompatibility.hpp
│   │
│   ├───performance_compatibility
│   │       .keep
│   │       TPerformanceCompatibility.hpp
│   │
│   ├───protocol_compatibility
│   │       .keep
│   │       TProtocolCompatibility.hpp
│   │
│   ├───rules
│   │       TCompatibilityRule.hpp
│   │       TCompatibilityRuleSet.hpp
│   │
│   ├───severity
│   │       TCompatibilitySeverity.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───traits
│   │       .keep
│   │       TCompatibilityTraits.hpp
│   │
│   ├───views
│   │       TCompatibilityView.hpp
│   │
│   └───visibility_compatibility
│           .keep
│           TVisibilityCompatibility.hpp
│
├───diagnostics
│   │   TDiagnostics.hpp
│   │
│   ├───binding_views
│   │       .keep
│   │       TBindingDiagnosticView.hpp
│   │
│   ├───builders
│   │       TBridgeDiagnosticBuilder.hpp
│   │       TRegistryDiagnosticBuilder.hpp
│   │
│   ├───carrier_snapshots
│   │       .keep
│   │       TCarrierSnapshot.hpp
│   │
│   ├───categories
│   │       TDiagnosticCategory.hpp
│   │
│   ├───channel_views
│   │       .keep
│   │       TChannelDiagnosticView.hpp
│   │
│   ├───collectors
│   │       TDiagnosticCollector.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───error_views
│   │       .keep
│   │       TErrorDiagnosticView.hpp
│   │
│   ├───ids
│   │       TDiagnosticId.hpp
│   │
│   ├───policies
│   │       TDiagnosticPolicy.hpp
│   │
│   ├───protocol_snapshots
│   │       .keep
│   │       TProtocolSnapshot.hpp
│   │
│   ├───records
│   │       TDiagnosticRecord.hpp
│   │
│   ├───reports
│   │       TDiagnosticReport.hpp
│   │
│   ├───session_views
│   │       .keep
│   │       TSessionDiagnosticView.hpp
│   │
│   ├───severity
│   │       TDiagnosticSeverity.hpp
│   │
│   ├───snapshots
│   │       TDiagnosticSnapshot.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───timing_views
│   │       .keep
│   │       TTimingDiagnosticView.hpp
│   │
│   └───views
│           TDiagnosticView.hpp
│
├───docs
├───integration_boundaries
│   │   TIntegrationBoundaryAbstractPorts.hpp
│   │
│   ├───capabilities
│   │       TIntegrationBoundaryCapability.hpp
│   │
│   ├───carriers
│   │       TBoundaryHandoffHandle.hpp
│   │       TBoundaryHandoffRequest.hpp
│   │
│   ├───descriptors
│   │       TIntegrationBoundaryDescriptor.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───diagnostics
│   │       .keep
│   │
│   ├───directions
│   │       TIntegrationBoundaryDirection.hpp
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───integration_skeleton
│   │   │   TFirstIntegrationSkeleton.hpp
│   │   │   TFirstIntegrationSkeletonBinding.hpp
│   │   │
│   │   ├───config
│   │   │       TFirstIntegrationSkeletonConfig.hpp
│   │   │
│   │   ├───factory
│   │   │       TFirstIntegrationSkeletonFactory.hpp
│   │   │
│   │   ├───ids
│   │   │       TFirstIntegrationSkeletonIdSet.hpp
│   │   │
│   │   ├───plans
│   │   │       TFirstIntegrationSkeletonModelPlan.hpp
│   │   │
│   │   └───reports
│   │           TFirstIntegrationSkeletonReport.hpp
│   │
│   ├───in_process_receivers
│   │       .keep
│   │       TInProcessReceiverPort.hpp
│   │
│   ├───kinds
│   │       TIntegrationBoundaryKind.hpp
│   │
│   ├───open_telemetry_ports
│   │       .keep
│   │       TOpenTelemetryPort.hpp
│   │
│   ├───persistence_ports
│   │       .keep
│   │       TPersistencePort.hpp
│   │
│   ├───policies
│   │       TIntegrationBoundaryPolicy.hpp
│   │
│   ├───ports
│   │       TIntegrationBoundaryPort.hpp
│   │
│   ├───registry_delivery
│   │       .keep
│   │       TRegistryDeliveryPort.hpp
│   │
│   ├───reports
│   │       TIntegrationBoundaryReport.hpp
│   │
│   ├───results
│   │       TBoundaryHandoffResult.hpp
│   │
│   ├───statuses
│   │       TBoundaryHandoffStatus.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───thin_c_abi_ports
│   │       .keep
│   │       TThinCAbiPort.hpp
│   │
│   ├───traits
│   │       TIntegrationBoundaryPortTraits.hpp
│   │
│   └───views
│           TIntegrationBoundaryPortView.hpp
│
├───obligations
│   │   SFINAE_Traits_Dysfunctionality_Report.md
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───plugin_adapters
│   │   ├───contracts
│   │   │       .keep
│   │   │       TPluginAdapter.hpp
│   │   │
│   │   ├───detail
│   │   │       .keep
│   │   │
│   │   ├───docs
│   │   │       .keep
│   │   │
│   │   ├───obligations
│   │   │       TPluginAdapterObligationProfile.hpp
│   │   │       TPluginAdapterObligationTraits.hpp
│   │   │       TPluginAdapterObligationTraits_ConceptLike.hpp
│   │   │       TPluginAdapterObligationTraits_CrtpAdjusted.hpp
│   │   │
│   │   ├───tests
│   │   │       .keep
│   │   │
│   │   ├───traits
│   │   │       .keep
│   │   │       TPluginAdapterTraits.hpp
│   │   │
│   │   └───views
│   │           .keep
│   │           TPluginAdapterView.hpp
│   │
│   ├───ports
│   │   │   TPort.hpp
│   │   │
│   │   ├───contracts
│   │   │       .keep
│   │   │       TPort.hpp
│   │   │
│   │   ├───detail
│   │   │       .keep
│   │   │
│   │   ├───docs
│   │   │       .keep
│   │   │
│   │   ├───obligations
│   │   │       TPortObligationProfile.hpp
│   │   │       TPortObligationTraits.hpp
│   │   │       TPortObligationTraits_ConceptLike.hpp
│   │   │       TPortObligationTraits_CrtpAdjusted.hpp
│   │   │
│   │   ├───tests
│   │   │       .keep
│   │   │
│   │   ├───traits
│   │   │       .keep
│   │   │       TPortTraits.hpp
│   │   │
│   │   └───views
│   │           .keep
│   │           TPortView.hpp
│   │
│   ├───reports
│   │       TObligationReport.hpp
│   │
│   ├───surface_pairs
│   │       TObligationSurfacePair.hpp
│   │
│   └───tests
│           .keep
│
├───participants
│   ├───descriptors
│   │       .keep
│   │       TParticipant.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───roles
│   │       .keep
│   │       TParticipantRole.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   └───views
│           .keep
│           TParticipantView.hpp
│
├───protocols
│   ├───common
│   │       .keep
│   │       TBridgeProtocol.hpp
│   │       TBridgeProtocolTraits.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───diagnostic_exchange
│   │       .keep
│   │       TDiagnosticExchangeProtocol.hpp
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───envelope_placement
│   │       .keep
│   │       TEnvelopePlacementProtocol.hpp
│   │
│   ├───frames
│   │       TBridgeProtocolFrame.hpp
│   │
│   ├───ids
│   │       TBridgeProtocolId.hpp
│   │
│   ├───kinds
│   │       TBridgeProtocolKind.hpp
│   │
│   ├───persistence_delivery
│   │       .keep
│   │       TPersistenceDeliveryProtocol.hpp
│   │
│   ├───plans
│   │       TBridgeProtocolPlan.hpp
│   │
│   ├───receiver_delivery
│   │       .keep
│   │       TReceiverDeliveryProtocol.hpp
│   │
│   ├───registry_delivery
│   │       .keep
│   │       TRegistryDeliveryProtocol.hpp
│   │
│   ├───results
│   │       TBridgeProtocolResult.hpp
│   │
│   ├───status
│   │       TBridgeProtocolStatus.hpp
│   │
│   ├───steps
│   │       TBridgeProtocolStep.hpp
│   │
│   ├───telemetry_export
│   │       .keep
│   │       TTelemetryExportProtocol.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───thin_c_abi
│   │       .keep
│   │       TThinCAbiProtocol.hpp
│   │
│   ├───traces
│   │       TBridgeProtocolTrace.hpp
│   │
│   └───views
│           TBridgeProtocolView.hpp
│
├───protocol_state
│   ├───detail
│   │       .keep
│   │
│   ├───diagnostics
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───lifecycle
│   │       .keep
│   │       TBridgeProtocolState.hpp
│   │
│   ├───snapshots
│   │       .keep
│   │       TBridgeProtocolSnapshot.hpp
│   │
│   ├───stages
│   │       .keep
│   │       TBridgeStage.hpp
│   │
│   ├───terminal_states
│   │       .keep
│   │       TBridgeTerminalState.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   └───transitions
│           .keep
│           TBridgeTransition.hpp
│
├───registries
│   │   TOptionalRegistries.hpp
│   │
│   ├───binding_registry
│   │       .keep
│   │       TBindingRegistry.hpp
│   │
│   ├───channel_registry
│   │       .keep
│   │       TChannelRegistry.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───optional_registries
│   │   ├───base
│   │   │       TBoundedRegistry.hpp
│   │   │
│   │   ├───entries
│   │   │       TRegistryEntry.hpp
│   │   │
│   │   ├───lookups
│   │   │       TRegistryLookupResult.hpp
│   │   │
│   │   ├───sets
│   │   │       TCommunicationContextRegistrySet.hpp
│   │   │
│   │   ├───snapshots
│   │   │       TRegistrySnapshot.hpp
│   │   │
│   │   ├───status
│   │   │       TRegistryEntryStatus.hpp
│   │   │
│   │   └───typed
│   │           TBindingRegistry.hpp
│   │           TBridgeProtocolRegistry.hpp
│   │           TBridgeRegistry.hpp
│   │           TChannelRegistry.hpp
│   │           TSessionRegistry.hpp
│   │
│   ├───participant_registry
│   │       .keep
│   │       TParticipantRegistry.hpp
│   │
│   ├───plugin_adapter_registry
│   │       .keep
│   │       TPluginAdapterRegistry.hpp
│   │
│   ├───port_registry
│   │       .keep
│   │       TPortRegistry.hpp
│   │
│   ├───protocol_registry
│   │       .keep
│   │       TProtocolRegistry.hpp
│   │
│   ├───session_registry
│   │       .keep
│   │       TSessionRegistry.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   └───views
│           .keep
│
├───sessions
│   ├───correlation
│   │       .keep
│   │       TSessionCorrelation.hpp
│   │
│   ├───detail
│   │       .keep
│   │
│   ├───docs
│   │       .keep
│   │
│   ├───handles
│   │       .keep
│   │
│   ├───ids
│   │       TSessionId.hpp
│   │
│   ├───lifecycle
│   │       .keep
│   │       TSession.hpp
│   │
│   ├───policies
│   │       TSessionPolicy.hpp
│   │
│   ├───requests
│   │       TSessionOpenRequest.hpp
│   │
│   ├───results
│   │       TSessionResult.hpp
│   │
│   ├───snapshots
│   │       TSessionSnapshot.hpp
│   │
│   ├───status
│   │       TSessionStatus.hpp
│   │
│   ├───tests
│   │       .keep
│   │
│   ├───traces
│   │       .keep
│   │
│   └───views
│           .keep
│           TSessionView.hpp
│
└───tests
    └───smoke-tests
        │   SFINAE_Traits_Dysfunctionality_Report.md
        │   w01_smoke_test.cpp
        │   w01_smoke_test.exe
        │   w02_smoke_test.cpp
        │   w02_smoke_test.exe
        │   w03_smoke_test.cpp
        │   w03_smoke_test.exe
        │   w04_smoke_test.cpp
        │   w04_smoke_test.exe
        │   w05_smoke_test.cpp
        │   w05_smoke_test.exe
        │   w06_smoke_test.cpp
        │   w07_smoke_test.cpp
        │   w07_smoke_test.exe
        │   w08_smoke_test.cpp
        │   w09_smoke_test.cpp
        │   w10_smoke_test.cpp
        │   w11_smoke_test.cpp
        │   w12_smoke_test.cpp
        │   w13_smoke_test.cpp
        │   w14a_smoke_test.cpp
        │   w14b_smoke_test.cpp
        │   w14c_smoke_test.cpp
        │   w15_smoke_test.cpp
        │
        └───tests
                .keep
                w07_smoke_test
                w07_smoke_test.cpp
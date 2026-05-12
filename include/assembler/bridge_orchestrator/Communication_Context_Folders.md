├───bindings
│   ├───adapter_port_bindings
│   ├───binding_policies
│   ├───binding_views
│   ├───compatibility
│   ├───concrete_bindings
│   │   ├───log_level_api
│   │   │   └───envelope_plugin_adapter
│   │   │       ├───carriers
│   │   │       ├───config
│   │   │       ├───factory
│   │   │       ├───state
│   │   │       └───views
│   │   └───write_side
│   │       ├───envelope_placement_port
│   │       │   ├───carriers
│   │       │   ├───config
│   │       │   ├───factory
│   │       │   ├───policies
│   │       │   ├───state
│   │       │   └───views
│   │       └───registry_delivery_plugin_adapter
│   ├───detail
│   ├───docs
│   ├───ids
│   ├───profiles
│   ├───results
│   ├───status
│   └───tests
├───bridge_carriers
│   ├───admission
│   ├───correlation
│   ├───destination
│   ├───detail
│   ├───docs
│   ├───errors
│   ├───handles
│   ├───readiness
│   ├───requests
│   ├───results
│   ├───signals
│   ├───tests
│   └───views
├───bridge_core
│   ├───budget
│   ├───config
│   ├───detail
│   ├───docs
│   ├───errors
│   ├───execution
│   ├───frames
│   ├───ids
│   ├───issues
│   ├───orchestration
│   ├───policies
│   ├───reports
│   ├───results
│   ├───snapshots
│   ├───status
│   ├───tests
│   ├───traces
│   ├───traits
│   └───views
├───channels
│   ├───detail
│   ├───docs
│   ├───policies
│   ├───profiles
│   ├───tests
│   ├───topology
│   └───views
├───compatibility
│   ├───binding_compatibility
│   ├───carrier_compatibility
│   ├───channel_compatibility
│   ├───detail
│   ├───dimensions
│   ├───docs
│   ├───issues
│   ├───matrix
│   ├───ownership_compatibility
│   ├───performance_compatibility
│   ├───protocol_compatibility
│   ├───rules
│   ├───severity
│   ├───tests
│   ├───traits
│   ├───views
│   └───visibility_compatibility
├───diagnostics
│   ├───binding_views
│   ├───builders
│   ├───carrier_snapshots
│   ├───categories
│   ├───channel_views
│   ├───collectors
│   ├───detail
│   ├───docs
│   ├───error_views
│   ├───ids
│   ├───policies
│   ├───protocol_snapshots
│   ├───records
│   ├───reports
│   ├───session_views
│   ├───severity
│   ├───snapshots
│   ├───tests
│   ├───timing_views
│   └───views
├───docs
├───integration_boundaries
│   ├───capabilities
│   ├───carriers
│   ├───descriptors
│   ├───detail
│   ├───diagnostics
│   ├───directions
│   ├───docs
│   ├───integration_skeleton
│   │   ├───config
│   │   ├───factory
│   │   ├───ids
│   │   ├───plans
│   │   └───reports
│   ├───in_process_receivers
│   ├───kinds
│   ├───open_telemetry_ports
│   ├───persistence_ports
│   ├───policies
│   ├───ports
│   ├───registry_delivery
│   ├───reports
│   ├───results
│   ├───statuses
│   ├───tests
│   ├───thin_c_abi_ports
│   ├───traits
│   └───views
├───obligations
│   ├───docs
│   ├───plugin_adapters
│   │   ├───contracts
│   │   ├───detail
│   │   ├───docs
│   │   ├───obligations
│   │   ├───tests
│   │   ├───traits
│   │   └───views
│   ├───ports
│   │   ├───contracts
│   │   ├───detail
│   │   ├───docs
│   │   ├───obligations
│   │   ├───tests
│   │   ├───traits
│   │   └───views
│   ├───reports
│   ├───surface_pairs
│   └───tests
├───participants
│   ├───descriptors
│   ├───detail
│   ├───docs
│   ├───roles
│   ├───tests
│   └───views
├───protocols
│   ├───common
│   ├───detail
│   ├───diagnostic_exchange
│   ├───docs
│   ├───envelope_placement
│   ├───frames
│   ├───ids
│   ├───kinds
│   ├───persistence_delivery
│   ├───plans
│   ├───receiver_delivery
│   ├───registry_delivery
│   ├───results
│   ├───status
│   ├───steps
│   ├───telemetry_export
│   ├───tests
│   ├───thin_c_abi
│   ├───traces
│   └───views
├───protocol_state
│   ├───detail
│   ├───diagnostics
│   ├───docs
│   ├───lifecycle
│   ├───snapshots
│   ├───stages
│   ├───terminal_states
│   ├───tests
│   └───transitions
├───registries
│   ├───binding_registry
│   ├───channel_registry
│   ├───detail
│   ├───docs
│   ├───optional_registries
│   │   ├───base
│   │   ├───entries
│   │   ├───lookups
│   │   ├───sets
│   │   ├───snapshots
│   │   ├───status
│   │   └───typed
│   ├───participant_registry
│   ├───plugin_adapter_registry
│   ├───port_registry
│   ├───protocol_registry
│   ├───session_registry
│   ├───tests
│   └───views
├───sessions
│   ├───correlation
│   ├───detail
│   ├───docs
│   ├───handles
│   ├───ids
│   ├───lifecycle
│   ├───policies
│   ├───requests
│   ├───results
│   ├───snapshots
│   ├───status
│   ├───tests
│   ├───traces
│   └───views
└───tests
    └───smoke-tests
        └───tests
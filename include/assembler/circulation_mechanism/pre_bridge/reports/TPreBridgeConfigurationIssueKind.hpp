#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

enum class TPreBridgeConfigurationIssueKind : std::uint8_t {
    none,
    invalid_default_profile_id,
    invalid_runtime_configuration,
    invalid_capacity_binding,
    invalid_ingress_binding,
    invalid_dispatch_binding,
    invalid_reference_supply_binding,
    invalid_diagnostics_binding,
    requires_read_side_runtime,
    incompatible_profile_kind
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

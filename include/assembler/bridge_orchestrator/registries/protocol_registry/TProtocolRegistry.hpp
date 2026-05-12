#pragma once

#include "assembler/communication_context/registries/bridge_protocol_registry/TBridgeProtocolRegistry.hpp"

/**
 * @file TProtocolRegistry.hpp
 * @brief Generic compatibility alias for the canonical ASCC bridge protocol registry.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * The precise canonical registry type is `TBridgeProtocolRegistry`, because
 * ASCC protocols are bridge-visible communication protocols.  This file keeps
 * the shorter historical/public path `TProtocolRegistry` as an alias template
 * without duplicating registry logic.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This alias must not create a separate protocol registry implementation,
 * execute protocols, invoke endpoints, schedule runtime work, act as a broker,
 * or become a service locator.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity, std::size_t PlanCapacity>
    using TProtocolRegistry = TBridgeProtocolRegistry<Capacity, PlanCapacity>;
}

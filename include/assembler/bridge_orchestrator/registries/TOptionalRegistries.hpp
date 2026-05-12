#pragma once

#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/entries/TRegistryEntry.hpp"
#include "assembler/communication_context/registries/optional_registries/lookups/TRegistryLookupResult.hpp"
#include "assembler/communication_context/registries/optional_registries/sets/TCommunicationContextRegistrySet.hpp"
#include "assembler/communication_context/registries/optional_registries/snapshots/TRegistrySnapshot.hpp"
#include "assembler/communication_context/registries/optional_registries/status/TRegistryEntryStatus.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBindingRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeProtocolRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TChannelRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TSessionRegistry.hpp"

/**
 * @file TOptionalRegistries.hpp
 * @brief Aggregate include for W11 optional registries.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - single aggregate include for the optional registry layer;
 * - stable availability marker for downstream waves and smoke tests;
 * - explicit optionality without registry mandate.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - aggregate include only;
 * - availability marker;
 * - no additional runtime behavior.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - mandatory runtime ownership;
 * - service locator behavior;
 * - dependency injection container behavior;
 * - scheduler, broker, queue, worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - persistence, database, telemetry, ABI, or downstream registry behavior;
 * - mutation of endpoint-owned resources;
 * - replacement of Channel, Binding, Session, Protocol, or Bridge semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W11 may depend on W01-W10 public Communication Context surfaces.
 * It must remain optional and must not be required by W14 concrete bindings
 * or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_W11_OPTIONAL_REGISTRIES_AVAILABLE = true;
}

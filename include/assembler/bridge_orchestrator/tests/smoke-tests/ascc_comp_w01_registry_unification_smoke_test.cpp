#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/registries/entries/TRegistryEntry.hpp"
#include "assembler/communication_context/registries/lookups/TRegistryLookupResult.hpp"
#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"
#include "assembler/communication_context/registries/status/TRegistryEntryStatus.hpp"
#include "assembler/communication_context/registries/binding_registry/TBindingRegistry.hpp"
#include "assembler/communication_context/registries/channel_registry/TChannelRegistry.hpp"
#include "assembler/communication_context/registries/session_registry/TSessionRegistry.hpp"
#include "assembler/communication_context/registries/bridge_protocol_registry/TBridgeProtocolRegistry.hpp"
#include "assembler/communication_context/registries/bridge_registry/TBridgeRegistry.hpp"
#include "assembler/communication_context/registries/participant_registry/TParticipantRegistry.hpp"
#include "assembler/communication_context/registries/plugin_adapter_registry/TPluginAdapterRegistry.hpp"
#include "assembler/communication_context/registries/port_registry/TPortRegistry.hpp"
#include "assembler/communication_context/registries/protocol_registry/TProtocolRegistry.hpp"
#include "assembler/communication_context/registries/sets/TCommunicationContextRegistrySet.hpp"

#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBindingRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TChannelRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TSessionRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeProtocolRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/sets/TCommunicationContextRegistrySet.hpp"

#include <type_traits>

int main()
{
    using namespace assembler::communication_context;

    static_assert(std::is_class<TRegistrySnapshot>::value,
                  "canonical registry snapshot must be available");

    static_assert(std::is_class<TChannelRegistry<4>>::value,
                  "canonical channel registry must be available");

    static_assert(std::is_class<TBindingRegistry<4>>::value,
                  "canonical binding registry must be available");

    static_assert(std::is_class<TSessionRegistry<4>>::value,
                  "canonical session registry must be available");

    static_assert(std::is_class<TBridgeProtocolRegistry<4, 12>>::value,
                  "canonical bridge protocol registry must be available");

    static_assert(std::is_class<TBridgeRegistry<4, 12>>::value,
                  "canonical bridge registry must be available");

    static_assert(std::is_class<TParticipantRegistry<4>>::value,
                  "canonical participant descriptor registry must be available");

    static_assert(std::is_class<TPluginAdapterRegistry<4>>::value,
                  "canonical plugin-adapter view registry must be available");

    static_assert(std::is_class<TPortRegistry<4>>::value,
                  "canonical port view registry must be available");

    static_assert(std::is_same<TProtocolRegistry<4, 12>, TBridgeProtocolRegistry<4, 12>>::value,
                  "TProtocolRegistry must remain an alias of TBridgeProtocolRegistry");

    static_assert(std::is_class<TCommunicationContextRegistrySet<4, 4, 4, 4, 4, 12>>::value,
                  "canonical registry set must be available");

    const auto snapshot = TRegistrySnapshot::make("registry_unification_smoke", 0u, 4u);

    return snapshot.is_valid() ? 0 : 1;
}

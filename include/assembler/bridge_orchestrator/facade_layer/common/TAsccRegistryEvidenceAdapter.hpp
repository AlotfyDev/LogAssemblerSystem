#pragma once

#include "assembler/communication_context/facade_layer/administrative/TAsccRegistryCatalogView.hpp"
#include "assembler/communication_context/registries/sets/TCommunicationContextRegistrySet.hpp"

/**
 * @file TAsccRegistryEvidenceAdapter.hpp
 * @brief Common facade adapter for projecting registry-set evidence.
 *
 * @section purpose Purpose
 * Converts `TCommunicationContextRegistrySet` into facade-safe registry catalog
 * evidence without exposing mutable registry internals.
 */

namespace assembler::communication_context
{
    struct TAsccRegistryEvidenceAdapter final
    {
        template <
            std::size_t ChannelCapacity,
            std::size_t BindingCapacity,
            std::size_t SessionCapacity,
            std::size_t ProtocolCapacity,
            std::size_t BridgeCapacity,
            std::size_t PlanCapacity>
        [[nodiscard]] static constexpr TAsccRegistryCatalogView to_catalog_view(
            const TCommunicationContextRegistrySet<
                ChannelCapacity,
                BindingCapacity,
                SessionCapacity,
                ProtocolCapacity,
                BridgeCapacity,
                PlanCapacity>& set) noexcept
        {
            return TAsccRegistryCatalogView{
                set.channels.count,
                set.bindings.registry.count,
                set.sessions.registry.count,
                set.protocols.registry.count,
                set.bridges.registry.count,
                "ascc_registry_catalog"
            };
        }
    };
}

#pragma once

#include "assembler/communication_context/facade_layer/administrative/TAsccComponentCapabilityCatalog.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentDescriptor.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"

namespace assembler::communication_context
{
    template <std::size_t CapabilityCapacity>
    struct TAsccAdministrativeFacade final
    {
        TAsccComponentDescriptor descriptor{};
        TAsccComponentProfileId default_profile{TAsccComponentProfileId::invalid()};
        TAsccComponentCapabilityCatalog<CapabilityCapacity> capability_catalog{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return descriptor.is_valid()
                && default_profile.is_valid()
                && capability_catalog.is_valid();
        }

        [[nodiscard]] constexpr bool declares_capability(
            TParticipantCapabilityKind capability) const noexcept
        {
            return capability_catalog.contains(capability);
        }
    };
}

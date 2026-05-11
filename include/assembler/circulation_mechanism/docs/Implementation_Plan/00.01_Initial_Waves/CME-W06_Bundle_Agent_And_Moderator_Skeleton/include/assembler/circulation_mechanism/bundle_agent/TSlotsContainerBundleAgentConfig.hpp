#pragma once

#include "assembler/circulation_mechanism/capacity/TCirculationCapacityProfile.hpp"

/*
    TSlotsContainerBundleAgentConfig.hpp

    Responsibility:
        Configuration surface for the BundleAgent skeleton.

    Does not own:
        - Runtime scaling.
        - Container allocation.
*/

namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerBundleAgentConfig final
{
    TCirculationCapacityProfile capacity_profile{};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return capacity_profile.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

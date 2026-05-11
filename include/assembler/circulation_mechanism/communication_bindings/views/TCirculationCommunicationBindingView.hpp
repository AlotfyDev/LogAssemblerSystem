#pragma once
#include "assembler/circulation_mechanism/communication_bindings/TCirculationCommunicationBindingDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TCirculationCommunicationBindingView final {
    TCirculationCommunicationBindingDescriptor descriptor{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return descriptor.is_valid() && descriptor.direction_descriptor_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return descriptor.status == TCommunicationBindingStatus::bound || descriptor.status == TCommunicationBindingStatus::ready; }
};
} // namespace circulation_mechanism
} // namespace assembler

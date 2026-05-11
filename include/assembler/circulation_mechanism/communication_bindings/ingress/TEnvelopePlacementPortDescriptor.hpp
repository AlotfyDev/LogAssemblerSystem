#pragma once
#include "TEnvelopePlacementPortId.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingStatus.hpp"
/*
    TEnvelopePlacementPortDescriptor.hpp

    Responsibility:
        Describes the CME ingress placement port.

    Non-ownership:
        Does not assemble envelopes, parse payload, compute refs, or expose internals.
*/
namespace assembler {
namespace circulation_mechanism {

struct TEnvelopePlacementPortDescriptor final {
    TEnvelopePlacementPortId port_id{};
    TCommunicationBindingStatus status{TCommunicationBindingStatus::unbound};
    bool accepts_prepared_envelope{true};
    bool exposes_container_internals{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return port_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TCommunicationBindingStatus::bound || status == TCommunicationBindingStatus::ready; }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept { return accepts_prepared_envelope && !exposes_container_internals; }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include <array>
#include <cstddef>
#include "TProtocolCarrierRequirement.hpp"
#include "TProtocolBindingRequirement.hpp"

namespace assembler::bridge_orchestrator::protocols::requirements {

struct TProtocolParticipantRequirement final {
    std::uint64_t requirement_id{0};
    TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
    TParticipantRole required_role{TParticipantRole::unknown};
    bool required{true};
    std::string_view note{};
    constexpr bool is_valid() const noexcept { return requirement_id != 0 && protocol != TBridgeProtocolKind::unknown && required_role != TParticipantRole::unknown; }
};

template <std::size_t ParticipantCapacity, std::size_t CarrierCapacity, std::size_t BindingCapacity>
struct TProtocolRequirementSet final {
    std::array<TProtocolParticipantRequirement, ParticipantCapacity> participants{};
    std::array<TProtocolCarrierRequirement, CarrierCapacity> carriers{};
    std::array<TProtocolBindingRequirement, BindingCapacity> bindings{};
    std::size_t participant_count{0};
    std::size_t carrier_count{0};
    std::size_t binding_count{0};

    constexpr bool add_participant_requirement(TProtocolParticipantRequirement r) noexcept { if (!r.is_valid() || participant_count >= ParticipantCapacity) return false; participants[participant_count++] = r; return true; }
    constexpr bool add_carrier_requirement(TProtocolCarrierRequirement r) noexcept { if (!r.is_valid() || carrier_count >= CarrierCapacity) return false; carriers[carrier_count++] = r; return true; }
    constexpr bool add_binding_requirement(TProtocolBindingRequirement r) noexcept { if (!r.is_valid() || binding_count >= BindingCapacity) return false; bindings[binding_count++] = r; return true; }
    constexpr bool is_valid() const noexcept { return participant_count > 0 && carrier_count > 0 && binding_count > 0; }

    static constexpr TProtocolRequirementSet<4, 12, 2> envelope_placement_requirements() noexcept {
        TProtocolRequirementSet<4, 12, 2> set{};
        set.add_participant_requirement({1, TBridgeProtocolKind::envelope_placement, TParticipantRole::content_provider, true, "source/content side"});
        set.add_participant_requirement({2, TBridgeProtocolKind::envelope_placement, TParticipantRole::receiver_provider, true, "receiver/host side"});
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(1, TBridgeProtocolKind::envelope_placement, TParticipantRole::content_provider, TParticipantCapabilityKind::prepares_placement_request, TAsccCarrierKind::placement_request, TParticipantCapabilityDirection::produces_carrier));
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(2, TBridgeProtocolKind::envelope_placement, TParticipantRole::receiver_provider, TParticipantCapabilityKind::accepts_placement_request, TAsccCarrierKind::placement_request, TParticipantCapabilityDirection::consumes_carrier));
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(3, TBridgeProtocolKind::envelope_placement, TParticipantRole::receiver_provider, TParticipantCapabilityKind::produces_placement_handle, TAsccCarrierKind::placement_handle, TParticipantCapabilityDirection::produces_carrier));
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(4, TBridgeProtocolKind::envelope_placement, TParticipantRole::content_provider, TParticipantCapabilityKind::accepts_placement_handle, TAsccCarrierKind::placement_handle, TParticipantCapabilityDirection::consumes_carrier));
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(5, TBridgeProtocolKind::envelope_placement, TParticipantRole::content_provider, TParticipantCapabilityKind::emits_load_signal, TAsccCarrierKind::load_signal, TParticipantCapabilityDirection::produces_carrier));
        set.add_carrier_requirement(TProtocolCarrierRequirement::make(6, TBridgeProtocolKind::envelope_placement, TParticipantRole::receiver_provider, TParticipantCapabilityKind::supports_readiness_view, TAsccCarrierKind::readiness_view, TParticipantCapabilityDirection::produces_carrier));
        set.add_binding_requirement(TProtocolBindingRequirement::envelope_placement());
        return set;
    }
};

} // namespace assembler::bridge_orchestrator::protocols::requirements

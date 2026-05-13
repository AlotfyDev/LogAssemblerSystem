#include "assembler/communication_context/participants/capabilities/TParticipantCapabilitySurface.hpp"

int main()
{
    using namespace assembler::communication_context;

    static_assert(ASCC_COMP_W03_PARTICIPANT_CAPABILITY_SURFACE_AVAILABLE,
                  "W03 participant capability surface must be available");

    auto content_caps = TParticipantCarrierCapabilitySet<8>::make("content_provider_caps");
    auto receiver_caps = TParticipantCarrierCapabilitySet<8>::make("receiver_provider_caps");

    const auto content_request = TParticipantCarrierCapability::make(
        TParticipantCapabilityId::from_value(1u),
        TParticipantRole::content_provider,
        TParticipantCapabilityKind::prepares_request_carrier,
        TAsccCarrierKind::placement_request,
        TParticipantCapabilityDirection::produces_carrier,
        TBridgeProtocolKind::envelope_placement,
        true,
        "content provider produces placement request");

    const auto receiver_request = TParticipantCarrierCapability::make(
        TParticipantCapabilityId::from_value(2u),
        TParticipantRole::receiver_provider,
        TParticipantCapabilityKind::accepts_request_carrier,
        TAsccCarrierKind::placement_request,
        TParticipantCapabilityDirection::consumes_carrier,
        TBridgeProtocolKind::envelope_placement,
        true,
        "receiver consumes placement request");

    const auto receiver_handle = TParticipantCarrierCapability::make(
        TParticipantCapabilityId::from_value(3u),
        TParticipantRole::receiver_provider,
        TParticipantCapabilityKind::produces_handle_carrier,
        TAsccCarrierKind::placement_handle,
        TParticipantCapabilityDirection::produces_carrier,
        TBridgeProtocolKind::envelope_placement,
        true,
        "receiver produces placement handle");

    const auto content_handle = TParticipantCarrierCapability::make(
        TParticipantCapabilityId::from_value(4u),
        TParticipantRole::content_provider,
        TParticipantCapabilityKind::accepts_handle_carrier,
        TAsccCarrierKind::placement_handle,
        TParticipantCapabilityDirection::consumes_carrier,
        TBridgeProtocolKind::envelope_placement,
        true,
        "content provider consumes placement handle");

    if (!content_caps.add(content_request)) return 1;
    if (!content_caps.add(content_handle)) return 2;
    if (!receiver_caps.add(receiver_request)) return 3;
    if (!receiver_caps.add(receiver_handle)) return 4;

    const auto content_request_req = TParticipantCapabilityRequirement::make(
        1u,
        TParticipantRole::content_provider,
        TParticipantCapabilityKind::prepares_request_carrier,
        TAsccCarrierKind::placement_request,
        TParticipantCapabilityDirection::produces_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    const auto receiver_request_req = TParticipantCapabilityRequirement::make(
        2u,
        TParticipantRole::receiver_provider,
        TParticipantCapabilityKind::accepts_request_carrier,
        TAsccCarrierKind::placement_request,
        TParticipantCapabilityDirection::consumes_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    const auto receiver_handle_req = TParticipantCapabilityRequirement::make(
        3u,
        TParticipantRole::receiver_provider,
        TParticipantCapabilityKind::produces_handle_carrier,
        TAsccCarrierKind::placement_handle,
        TParticipantCapabilityDirection::produces_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    const auto content_handle_req = TParticipantCapabilityRequirement::make(
        4u,
        TParticipantRole::content_provider,
        TParticipantCapabilityKind::accepts_handle_carrier,
        TAsccCarrierKind::placement_handle,
        TParticipantCapabilityDirection::consumes_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    if (!content_caps.match(content_request_req).matched()) return 5;
    if (!receiver_caps.match(receiver_request_req).matched()) return 6;
    if (!receiver_caps.match(receiver_handle_req).matched()) return 7;
    if (!content_caps.match(content_handle_req).matched()) return 8;

    const auto wrong_direction = TParticipantCapabilityRequirement::make(
        5u,
        TParticipantRole::content_provider,
        TParticipantCapabilityKind::prepares_request_carrier,
        TAsccCarrierKind::placement_request,
        TParticipantCapabilityDirection::consumes_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    if (content_caps.match(wrong_direction).status != TParticipantCapabilityMatchStatus::wrong_direction)
    {
        return 9;
    }

    const auto diagnostic_illegal_handle = TParticipantCapabilityRequirement::make(
        6u,
        TParticipantRole::diagnostic_observer,
        TParticipantCapabilityKind::produces_handle_carrier,
        TAsccCarrierKind::placement_handle,
        TParticipantCapabilityDirection::produces_carrier,
        TBridgeProtocolKind::envelope_placement,
        true);

    if (!content_caps.match(diagnostic_illegal_handle).failed())
    {
        return 10;
    }

    auto report = TParticipantCapabilityReport::make(
        TParticipantCapabilityView::make(
            TParticipantRole::content_provider,
            2u,
            content_caps.count,
            true,
            "content_provider_capability_view"));

    report.observe(content_caps.match(content_request_req));
    report.observe(content_caps.match(content_handle_req));

    if (!report.passed()) return 11;

    return 0;
}

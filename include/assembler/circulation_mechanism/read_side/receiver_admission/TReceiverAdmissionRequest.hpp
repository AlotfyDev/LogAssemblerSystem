#pragma once
#include "TReceiverAdmissionRequestId.hpp"
#include "TReceiverAdmissionRequestStatus.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/post_bridge_capacity/TPostBridgeCapacityProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/receiver_context/TReceiverContextDescriptor.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/failed_dispatch/TFailedDispatchKind.hpp"

/*
    TReceiverAdmissionRequest.hpp

    Current responsibility:
        Describes a request to admit post-bridge material into read-side receiver-facing circulation.

    Production capabilities:
        - request identity/status
        - capacity snapshot
        - receiver context snapshot
        - failure kind hint
        - validity and receiver readiness helpers

    Explicit non-ownership:
        - Does not carry payload bytes.
        - Does not call receiver.
        - Does not mutate capacity profile.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionRequest final {
    TReceiverAdmissionRequestId request_id{};
    TReceiverAdmissionRequestStatus status{TReceiverAdmissionRequestStatus::undefined};
    read_side_circulation_profile::TPostBridgeCapacityProfile capacity{};
    read_side_circulation_profile::TReceiverContextDescriptor receiver{};
    read_side_circulation_profile::TFailedDispatchKind failure_hint{read_side_circulation_profile::TFailedDispatchKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return request_id.is_valid()
            && status == TReceiverAdmissionRequestStatus::ready
            && capacity.is_valid()
            && receiver.is_valid();
    }

    [[nodiscard]] constexpr bool receiver_ready() const noexcept {
        return receiver.is_valid();
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

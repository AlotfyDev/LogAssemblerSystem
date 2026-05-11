#pragma once
#include "TReceiverAcknowledgementId.hpp"
#include "TReceiverAcknowledgementState.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReceiverAcknowledgementRecord final {
    TReceiverAcknowledgementId acknowledgement_id{};
    TReceiverAcknowledgementState state{TReceiverAcknowledgementState::unknown};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return acknowledgement_id.is_valid(); }
    [[nodiscard]] constexpr bool acknowledged() const noexcept { return state == TReceiverAcknowledgementState::acknowledged; }
    [[nodiscard]] constexpr bool rejected() const noexcept { return state == TReceiverAcknowledgementState::rejected; }
    [[nodiscard]] constexpr bool pending_or_required() const noexcept { return state == TReceiverAcknowledgementState::required || state == TReceiverAcknowledgementState::pending; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

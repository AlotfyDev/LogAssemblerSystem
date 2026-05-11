#pragma once
#include "../receiver_admission/TReceiverAdmissionDecision.hpp"
#include "../receiver_admission/TReceiverAdmissionControllerId.hpp"

/*
    TReceiverAdmissionView.hpp

    Current responsibility:
        Read-only projection of latest receiver admission decision.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionView final {
    TReceiverAdmissionControllerId controller_id{};
    TReceiverAdmissionDecision decision{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return controller_id.is_valid() && decision.is_valid();
    }

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return decision.accepted();
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

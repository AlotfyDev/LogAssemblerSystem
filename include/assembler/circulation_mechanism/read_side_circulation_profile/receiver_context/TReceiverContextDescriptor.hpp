#pragma once
#include "TReceiverContextId.hpp"
#include "TReceiverContextKind.hpp"
#include "TReceiverLifecycleExpectation.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReceiverContextDescriptor final {
    TReceiverContextId receiver_context_id{};
    TReceiverContextKind kind{TReceiverContextKind::unknown};
    TReceiverLifecycleExpectation lifecycle_expectation{TReceiverLifecycleExpectation::none};
    bool supports_backpressure{false};
    bool supports_retry{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return receiver_context_id.is_valid() && kind != TReceiverContextKind::unknown;
    }
    [[nodiscard]] constexpr bool acknowledgement_required() const noexcept {
        return lifecycle_expectation == TReceiverLifecycleExpectation::ack_required
            || lifecycle_expectation == TReceiverLifecycleExpectation::delayed_ack;
    }
    [[nodiscard]] constexpr bool retry_expected() const noexcept {
        return lifecycle_expectation == TReceiverLifecycleExpectation::retry_capable || supports_retry;
    }
    [[nodiscard]] constexpr bool persistence_expected() const noexcept {
        return lifecycle_expectation == TReceiverLifecycleExpectation::persistence_backed;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

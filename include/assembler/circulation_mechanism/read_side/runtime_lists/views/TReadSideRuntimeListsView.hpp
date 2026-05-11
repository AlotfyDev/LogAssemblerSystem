#pragma once
#include <cstdint>

/*
    TReadSideRuntimeListsView.hpp

    Responsibility:
        Read-only projection of read-side runtime list sizes.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideRuntimeListsView final {
    std::uint32_t failed_dispatch_count{0};
    std::uint32_t retry_count{0};
    std::uint32_t delayed_release_count{0};
    std::uint32_t receiver_ack_count{0};

    [[nodiscard]] constexpr bool has_pending_work() const noexcept {
        return failed_dispatch_count > 0U || retry_count > 0U || delayed_release_count > 0U || receiver_ack_count > 0U;
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

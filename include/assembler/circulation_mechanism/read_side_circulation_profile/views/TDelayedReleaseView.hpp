#pragma once
#include "../delayed_release/TDelayedReleaseRecord.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TDelayedReleaseView final {
    TDelayedReleaseRecord record{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return record.is_valid(); }
    [[nodiscard]] constexpr bool pending() const noexcept { return record.pending(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

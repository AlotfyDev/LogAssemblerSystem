#pragma once
#include "../failed_dispatch/TFailedDispatchRecord.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TFailedDispatchView final {
    TFailedDispatchRecord record{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return record.is_valid(); }
    [[nodiscard]] constexpr bool retry_candidate() const noexcept { return record.retry_candidate(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

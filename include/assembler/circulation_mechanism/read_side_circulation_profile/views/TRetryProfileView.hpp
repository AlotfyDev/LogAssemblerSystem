#pragma once
#include "../retry/TReadSideRetryProfile.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TRetryProfileView final {
    TReadSideRetryProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid(); }
    [[nodiscard]] constexpr bool enabled() const noexcept { return profile.retry_enabled(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

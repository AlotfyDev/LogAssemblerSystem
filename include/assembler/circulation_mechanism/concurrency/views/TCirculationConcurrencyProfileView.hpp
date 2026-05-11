#pragma once
#include "../TCirculationConcurrencyProfile.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TCirculationConcurrencyProfileView final {
    TCirculationConcurrencyProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return profile.accepted(); }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler

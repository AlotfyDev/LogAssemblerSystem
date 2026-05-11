#pragma once
#include "TReadSideListStatus.hpp"
#include <cstdint>

namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideListOperationResult final {
    TReadSideListStatus status{TReadSideListStatus::not_attempted};
    std::uint32_t size_after{0};

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return status == TReadSideListStatus::accepted;
    }

    [[nodiscard]] constexpr bool rejected() const noexcept {
        return !accepted();
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

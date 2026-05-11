#pragma once
#include "TDispatchReadyView.hpp"
#include "TDispatchExposureView.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatcherView final {
    TDispatchReadyView readiness{};
    TDispatchExposureView exposure{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return readiness.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

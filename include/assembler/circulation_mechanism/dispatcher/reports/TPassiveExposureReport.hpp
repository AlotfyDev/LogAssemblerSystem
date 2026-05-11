#pragma once
#include "TDispatchExposureReport.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TPassiveExposureReport final {
    TDispatchExposureReport base{};
    bool bridge_observation_required{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return base.is_valid() && base.exposed(); }
};
} // namespace circulation_mechanism
} // namespace assembler

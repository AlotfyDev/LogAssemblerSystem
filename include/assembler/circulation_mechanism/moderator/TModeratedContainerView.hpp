#pragma once
#include "TModeratorReadinessView.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TModeratedContainerView final {
    TModeratorReadinessView readiness{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return readiness.is_valid(); }
    [[nodiscard]] constexpr bool ingress_ready_exposable() const noexcept { return readiness.can_expose_ingress_ready(); }
};
} // namespace circulation_mechanism
} // namespace assembler

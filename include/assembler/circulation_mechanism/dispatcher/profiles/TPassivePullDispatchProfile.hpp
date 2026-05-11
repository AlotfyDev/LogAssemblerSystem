#pragma once
#include "TDispatchProfileKind.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TPassivePullDispatchProfile final {
    TDispatchProfileKind kind{TDispatchProfileKind::passive_pull};
    bool bridge_observation_required_for_release{false};
    bool exposure_expiration_enabled{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return kind == TDispatchProfileKind::passive_pull; }
};
} // namespace circulation_mechanism
} // namespace assembler

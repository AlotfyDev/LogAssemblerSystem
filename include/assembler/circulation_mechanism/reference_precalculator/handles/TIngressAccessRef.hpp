#pragma once
#include "TSlotAccessRef.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressAccessRef final {
    TSlotAccessRef base{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return base.is_valid() && base.kind == TAccessRefKind::ingress_access && base.direction == TAccessRefDirection::ingress; }
    [[nodiscard]] constexpr bool can_be_consumed_by_ingress() const noexcept { return is_valid() && base.can_be_consumed(); }
};
} // namespace circulation_mechanism
} // namespace assembler

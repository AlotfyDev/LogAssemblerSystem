#pragma once
#include "TSlotAccessRef.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchAccessRef final {
    TSlotAccessRef base{};
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return base.is_valid() && base.kind == TAccessRefKind::dispatch_access && base.direction == TAccessRefDirection::dispatch;
    }
    [[nodiscard]] constexpr bool can_be_consumed_by_dispatcher() const noexcept { return is_valid() && base.can_be_consumed(); }
};
} // namespace circulation_mechanism
} // namespace assembler

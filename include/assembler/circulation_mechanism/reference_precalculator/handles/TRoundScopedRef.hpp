#pragma once
#include "TSlotAccessRef.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TRoundScopedRef final {
    TSlotAccessRef base{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return base.is_valid() && base.scope.has_round_scope(); }
};
} // namespace circulation_mechanism
} // namespace assembler

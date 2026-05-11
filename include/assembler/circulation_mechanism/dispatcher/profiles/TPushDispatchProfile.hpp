#pragma once
#include "TDispatchProfileKind.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TPushDispatchProfile final {
    TDispatchProfileKind kind{TDispatchProfileKind::push};
    bool enabled{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return kind == TDispatchProfileKind::push; }
    [[nodiscard]] constexpr bool is_enabled() const noexcept { return enabled && is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler

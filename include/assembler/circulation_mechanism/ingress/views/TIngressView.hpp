#pragma once
#include "assembler/circulation_mechanism/ingress/TIngressId.hpp"
#include "assembler/circulation_mechanism/ingress/TIngressState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressView final {
    TIngressId ingress_id{};
    TIngressState state{TIngressState::uninitialized};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return ingress_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return ingress_ready(state); }
};
} // namespace circulation_mechanism
} // namespace assembler

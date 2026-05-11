#pragma once
#include "TIngressView.hpp"
#include "assembler/circulation_mechanism/ingress/boundary/TIngressBoundaryDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressAdmissionView final {
    TIngressView ingress{};
    TIngressBoundaryDescriptor boundary{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return ingress.is_valid() && boundary.is_valid(); }
    [[nodiscard]] constexpr bool can_accept() const noexcept { return ingress.ready() && boundary.ready() && boundary.boundary_safe(); }
};
} // namespace circulation_mechanism
} // namespace assembler

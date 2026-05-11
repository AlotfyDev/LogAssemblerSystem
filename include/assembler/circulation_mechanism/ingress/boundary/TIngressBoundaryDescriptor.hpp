#pragma once
#include "TIngressBoundaryId.hpp"
#include "TIngressBoundaryStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressBoundaryDescriptor final {
    TIngressBoundaryId boundary_id{};
    TIngressBoundaryStatus status{TIngressBoundaryStatus::unbound};
    bool accepts_prepared_envelope{true};
    bool exposes_container_internals{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return boundary_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TIngressBoundaryStatus::bound || status == TIngressBoundaryStatus::ready; }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept { return accepts_prepared_envelope && !exposes_container_internals; }
};
} // namespace circulation_mechanism
} // namespace assembler

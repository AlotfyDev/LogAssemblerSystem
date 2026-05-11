#pragma once
#include "TDispatchBoundaryId.hpp"
#include "TDispatchBoundaryStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchBoundaryDescriptor final {
    TDispatchBoundaryId boundary_id{};
    TDispatchBoundaryStatus status{TDispatchBoundaryStatus::unbound};
    bool supports_passive_pull{true};
    bool exposes_mutable_internals{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return boundary_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TDispatchBoundaryStatus::bound || status == TDispatchBoundaryStatus::ready; }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept { return supports_passive_pull && !exposes_mutable_internals; }
};
} // namespace circulation_mechanism
} // namespace assembler

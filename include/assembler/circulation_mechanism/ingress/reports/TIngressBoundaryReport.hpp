#pragma once
#include "TIngressReportId.hpp"
#include "assembler/circulation_mechanism/ingress/boundary/TIngressBoundaryDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressBoundaryReport final {
    TIngressReportId report_id{};
    TIngressBoundaryDescriptor boundary{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && boundary.is_valid(); }
    [[nodiscard]] constexpr bool ready_and_safe() const noexcept { return boundary.ready() && boundary.boundary_safe(); }
};
} // namespace circulation_mechanism
} // namespace assembler

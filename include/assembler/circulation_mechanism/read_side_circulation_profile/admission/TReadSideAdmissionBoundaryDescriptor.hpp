#pragma once
#include "TReadSideAdmissionBoundaryId.hpp"
#include "TReadSideAdmissionMode.hpp"
#include "TReadSideAdmissionStatus.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideAdmissionBoundaryDescriptor final {
    TReadSideAdmissionBoundaryId boundary_id{};
    TReadSideAdmissionMode mode{TReadSideAdmissionMode::passive_pull_from_bridge};
    TReadSideAdmissionStatus status{TReadSideAdmissionStatus::unbound};
    bool accepts_post_bridge_material{true};
    bool exposes_pre_bridge_internals{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return boundary_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TReadSideAdmissionStatus::bound || status == TReadSideAdmissionStatus::ready; }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept { return accepts_post_bridge_material && !exposes_pre_bridge_internals; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

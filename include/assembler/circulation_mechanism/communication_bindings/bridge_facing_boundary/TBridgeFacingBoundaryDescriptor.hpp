#pragma once
#include "TBridgeFacingBoundaryId.hpp"
#include "TBridgeFacingBoundaryStatus.hpp"
#include "assembler/circulation_mechanism/communication_bindings/exposure_contracts/TExposureContractDescriptor.hpp"
/*
    TBridgeFacingBoundaryDescriptor.hpp

    Responsibility:
        Describes the boundary toward bridge without owning bridge runtime.

    Non-ownership:
        Does not implement bridge session, bridge protocol, recovery, or receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {

struct TBridgeFacingBoundaryDescriptor final {
    TBridgeFacingBoundaryId boundary_id{};
    TBridgeFacingBoundaryStatus status{TBridgeFacingBoundaryStatus::undefined};
    TExposureContractDescriptor exposure_contract{};
    bool bridge_runtime_owned_elsewhere{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return boundary_id.is_valid(); }
    [[nodiscard]] constexpr bool ready_and_safe() const noexcept {
        return status == TBridgeFacingBoundaryStatus::ready && exposure_contract.boundary_safe() && bridge_runtime_owned_elsewhere;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

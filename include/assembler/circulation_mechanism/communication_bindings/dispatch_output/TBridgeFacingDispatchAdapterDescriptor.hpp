#pragma once
#include "TDispatchOutputAdapterId.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingStatus.hpp"
#include "assembler/circulation_mechanism/communication_bindings/exposure_contracts/TExposureContractDescriptor.hpp"
/*
    TBridgeFacingDispatchAdapterDescriptor.hpp

    Responsibility:
        Describes dispatch output adapter readiness and exposure contract.

    Non-ownership:
        Does not execute bridge protocol or copy/move payload.
*/
namespace assembler {
namespace circulation_mechanism {

struct TBridgeFacingDispatchAdapterDescriptor final {
    TDispatchOutputAdapterId adapter_id{};
    TCommunicationBindingStatus status{TCommunicationBindingStatus::unbound};
    bool supports_passive_pull{true};
    bool supports_push{false};
    TExposureContractDescriptor exposure_contract{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return adapter_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TCommunicationBindingStatus::bound || status == TCommunicationBindingStatus::ready; }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept {
        return ready() && supports_passive_pull && exposure_contract.boundary_safe();
    }
};
} // namespace circulation_mechanism
} // namespace assembler

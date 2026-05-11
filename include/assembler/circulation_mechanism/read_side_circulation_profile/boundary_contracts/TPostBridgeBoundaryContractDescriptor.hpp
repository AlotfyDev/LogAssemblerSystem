#pragma once
#include "TPostBridgeBoundaryContractId.hpp"
#include "TPostBridgeTransferSemantic.hpp"
#include "TPostBridgeBoundaryContractStatus.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TPostBridgeBoundaryContractDescriptor final {
    TPostBridgeBoundaryContractId contract_id{};
    TPostBridgeTransferSemantic transfer_semantic{TPostBridgeTransferSemantic::unknown};
    TPostBridgeBoundaryContractStatus status{TPostBridgeBoundaryContractStatus::undefined};
    bool receiver_acknowledgement_visible{false};
    bool bridge_runtime_owned_elsewhere{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return contract_id.is_valid() && transfer_semantic != TPostBridgeTransferSemantic::unknown;
    }
    [[nodiscard]] constexpr bool compatible() const noexcept {
        return is_valid() && status == TPostBridgeBoundaryContractStatus::compatible && bridge_runtime_owned_elsewhere;
    }
    [[nodiscard]] constexpr bool transfer_is_external_contract() const noexcept {
        return transfer_semantic == TPostBridgeTransferSemantic::copy
            || transfer_semantic == TPostBridgeTransferSemantic::move
            || transfer_semantic == TPostBridgeTransferSemantic::borrowed_view
            || transfer_semantic == TPostBridgeTransferSemantic::exposure_only
            || transfer_semantic == TPostBridgeTransferSemantic::implementation_defined;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

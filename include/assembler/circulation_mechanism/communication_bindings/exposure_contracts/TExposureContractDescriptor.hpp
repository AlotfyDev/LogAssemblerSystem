#pragma once
#include "TExposureContractId.hpp"
#include "TExposureMode.hpp"
#include "TExposureMaterialKind.hpp"
/*
    TExposureContractDescriptor.hpp

    Responsibility:
        Declares what may cross an output exposure boundary.

    Production capabilities:
        - passive/push/hybrid/notification mode
        - material kind classification
        - mutable internal exposure guard
        - copy/move ownership guard

    Non-ownership:
        Does not execute payload movement or bridge protocol.
*/
namespace assembler {
namespace circulation_mechanism {

struct TExposureContractDescriptor final {
    TExposureContractId contract_id{};
    TExposureMode mode{TExposureMode::none};
    TExposureMaterialKind material_kind{TExposureMaterialKind::none};
    bool exposes_mutable_internals{false};
    bool cme_owns_copy_move{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return contract_id.is_valid() && mode != TExposureMode::none && material_kind != TExposureMaterialKind::none;
    }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept {
        return is_valid() && !exposes_mutable_internals && !cme_owns_copy_move;
    }
};
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
#include "TReadSideProfileId.hpp"
#include "TReadSideProfileStatus.hpp"
#include "TReadSideProfileValidationResult.hpp"
#include "admission/TReadSideAdmissionBoundaryDescriptor.hpp"
#include "receiver_context/TReceiverContextDescriptor.hpp"
#include "boundary_contracts/TPostBridgeBoundaryContractDescriptor.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideCirculationProfile final {
    TReadSideProfileId profile_id{};
    TReadSideProfileStatus status{TReadSideProfileStatus::undefined};
    TReadSideAdmissionBoundaryDescriptor admission{};
    TReceiverContextDescriptor receiver{};
    TPostBridgeBoundaryContractDescriptor boundary_contract{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile_id.is_valid() && admission.is_valid() && receiver.is_valid() && boundary_contract.is_valid();
    }

    [[nodiscard]] constexpr TReadSideProfileValidationResult validate() const noexcept {
        if (!profile_id.is_valid()) return rejected_profile(TReadSideProfileIssueKind::missing_receiver_context);
        if (!admission.is_valid() || !admission.ready() || !admission.boundary_safe()) return rejected_profile(TReadSideProfileIssueKind::missing_admission_boundary);
        if (!receiver.is_valid()) return rejected_profile(TReadSideProfileIssueKind::missing_receiver_context);
        if (!boundary_contract.is_valid() || !boundary_contract.compatible()) return rejected_profile(TReadSideProfileIssueKind::missing_bridge_contract);
        if (!boundary_contract.transfer_is_external_contract()) return rejected_profile(TReadSideProfileIssueKind::unsupported_transfer_semantic);
        if (receiver.acknowledgement_required() && !boundary_contract.receiver_acknowledgement_visible) {
            return rejected_profile(TReadSideProfileIssueKind::ack_required_but_not_visible);
        }
        if (status != TReadSideProfileStatus::ready && status != TReadSideProfileStatus::active) {
            return rejected_profile(TReadSideProfileIssueKind::boundary_mismatch);
        }
        return accepted_profile();
    }

    [[nodiscard]] constexpr bool ready() const noexcept {
        return validate().accepted;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

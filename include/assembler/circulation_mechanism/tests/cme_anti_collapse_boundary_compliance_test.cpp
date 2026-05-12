
#include "assembler/circulation_mechanism/circulation_mechanism_ids.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_safe_points.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_views.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reports.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_diagnostics.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_slot.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_container.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_container_registry.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_waiting_list.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_round_manager.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reference_precalculator.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_ingress.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_dispatcher.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_release_recycle.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_eviction.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_communication_bindings.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w01.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w02.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w03.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w04.hpp"

#include <type_traits>

using namespace assembler::circulation_mechanism;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    // 1. IDs are distinct and must not collapse into one another.
    static_assert(!std::is_same<TContainerId, TContainerRegistryIndex>::value,
        "ContainerId must not collapse into ContainerRegistryIndex.");
    static_assert(!std::is_same<TSlotIndex, TContainerRegistryIndex>::value,
        "SlotIndex must not collapse into registry index.");
    static_assert(!std::is_convertible<TContainerRegistryIndex, TContainerId>::value,
        "Registry index must not implicitly convert to container id.");

    // 2. Views are not mutable aggregate handles.
    static_assert(!std::is_aggregate<TReadOnlyViewDescriptor>::value,
        "Read-only view descriptor must not expose mutable aggregate fields.");
    constexpr auto local_view = TReadOnlyViewDescriptor::local_snapshot(TViewId::from_raw(1));
    static_assert(local_view.validate().accepted, "Local view should validate.");
    constexpr TReadOnlyViewDescriptor unsafe_boundary_view{
        TViewId::from_raw(2),
        TViewScope::boundary_facing,
        TViewStability::snapshot,
        TViewVisibility::internal_only
    };
    static_assert(unsafe_boundary_view.validate().rejected(),
        "Boundary-facing view must be boundary_safe.");

    // 3. Reports are evidence only and must reject downstream proof claims.
    constexpr TReportDescriptor false_delivery_proof{
        TReportId::from_raw(10),
        TReportKind::boundary,
        TReportStatus::complete,
        TReportScopeKind::boundary,
        TReportEvidenceKind::boundary_observed,
        true,
        false
    };
    static_assert(false_delivery_proof.validate().issue == TReportContractIssueKind::downstream_proof_claim,
        "Report must not claim downstream delivery proof.");

    constexpr TReportDescriptor authority_expansion{
        TReportId::from_raw(11),
        TReportKind::operational,
        TReportStatus::complete,
        TReportScopeKind::local_component,
        TReportEvidenceKind::action_completed,
        false,
        true
    };
    static_assert(authority_expansion.validate().issue == TReportContractIssueKind::authority_expansion_claim,
        "Report must not expand authority.");

    // 4. Diagnostics classify issues but do not execute recovery.
    constexpr auto issue = TDiagnosticIssue::invariant(
        TDiagnosticIssueId::from_raw(20),
        TDiagnosticIssueKind::invariant_violation,
        TDiagnosticSeverity::critical
    );
    static_assert(issue.is_valid(), "Diagnostic issue valid.");
    static_assert(issue.is_error(), "Critical diagnostic is error.");
    static_assert(issue.hint() == TDiagnosticResolutionHint::reject_operation,
        "Resolution hint is non-executing guidance.");

    // 5. Waiting lists store indices, not payloads.
    static_assert(std::is_trivially_copyable<TWaitingListEntry>::value,
        "Waiting-list entry should remain a lightweight index carrier.");
    TIngressWaitingList<1> ingress_list{};
    auto accepted = ingress_list.try_push(TWaitingListEntry{
        TContainerRegistryIndex::from_raw(1),
        TContainerState::ingress_ready,
        0U,
        1U
    });
    if (!accepted.accepted()) return 1;

    auto wrong_state = ingress_list.try_push(TWaitingListEntry{
        TContainerRegistryIndex::from_raw(2),
        TContainerState::dispatch_candidate,
        0U,
        1U
    });
    if (wrong_state.accepted()) return 2;

    // 6. References are directional and scoped.
    constexpr TAccessRefScope scope{
        TContainerRegistryIndex::from_raw(1),
        TSlotIndex::from_raw(1),
        TRoundId::from_raw(1),
        1U,
        1U
    };
    constexpr TIngressAccessRef ingress_ref{TSlotAccessRef{
        TAccessRefId::from_raw(1),
        TAccessRefKind::ingress_access,
        TAccessRefDirection::ingress,
        scope,
        TReferenceValidityState::issued
    }};
    static_assert(ingress_ref.can_be_consumed_by_ingress(), "Ingress ref consumable by ingress.");

    constexpr TDispatchAccessRef wrong_dispatch_shape{TSlotAccessRef{
        TAccessRefId::from_raw(2),
        TAccessRefKind::ingress_access,
        TAccessRefDirection::ingress,
        scope,
        TReferenceValidityState::issued
    }};
    static_assert(!wrong_dispatch_shape.is_valid(),
        "Dispatch ref must not accept ingress-shaped reference.");

    // 7. Ingress executes placement but does not locate. It rejects unsafe boundary.
    constexpr TIngressBoundaryDescriptor bad_ingress_boundary{
        TIngressBoundaryId::from_raw(5),
        TIngressBoundaryStatus::ready,
        true,
        true
    };
    static_assert(!bad_ingress_boundary.boundary_safe(),
        "Ingress boundary exposing container internals is unsafe.");

    // 8. Dispatcher exposes but does not own bridge/copy/move semantics.
    constexpr TExposureContractDescriptor unsafe_mutable_exposure{
        TExposureContractId::from_raw(6),
        TExposureMode::passive_pull,
        TExposureMaterialKind::borrowed_payload_view,
        true,
        false
    };
    static_assert(!unsafe_mutable_exposure.boundary_safe(),
        "Mutable internal exposure must be blocked.");

    constexpr TExposureContractDescriptor cme_owned_move{
        TExposureContractId::from_raw(7),
        TExposureMode::passive_pull,
        TExposureMaterialKind::moved_payload,
        false,
        true
    };
    static_assert(!cme_owned_move.boundary_safe(),
        "CME must not own bridge-side copy/move semantics.");

    // 9. Safe points permit but do not execute guarded operations.
    constexpr TSafePointView unavailable_sp{
        TSafePointId::from_raw(8),
        TSafePointKind::container_reset,
        TSafePointState::unavailable,
        1U
    };
    static_assert(!TSafePointPolicy::can_perform(unavailable_sp, TSafePointKind::container_reset),
        "Unavailable safe point blocks operation.");

    // 10. Release/recycle is eligibility, not receiver proof.
    static_assert(TRecyclePolicy::can_release_exposure(TDispatchExposureState::passive_exposed) == TReleaseRecycleStatus::rejected_active_exposure,
        "Passive exposure is not automatically releasable.");
    static_assert(TRecyclePolicy::can_reset_container(TContainerState::reset_pending, TSafePointState::unavailable) == TReleaseRecycleStatus::rejected_missing_safe_point,
        "Reset requires safe point.");

    // 11. Eviction is safe-point and ref/round/exposure guarded.
    constexpr TEvictionCandidate unsafe_eviction{
        TEvictionCandidateId::from_raw(30),
        TContainerId::from_raw(31),
        TContainerRegistryIndex::from_raw(1),
        TContainerState::receiving,
        TContainerTimeRange{10, 20, true, true},
        TSafePointState::available,
        TReferenceValidityState::invalidated,
        TRoundState::closed,
        TDispatchExposureState::closed,
        TEvictionCandidateStatus::eligible
    };
    static_assert(unsafe_eviction.evaluate() == TEvictionEvaluationStatus::rejected_active_ingress,
        "Eviction must reject active ingress containers.");

    // 12. Read-side profile describes post-bridge readiness but does not execute bridge/receiver.
    constexpr rscp::TReadSideAdmissionBoundaryDescriptor read_admission{
        rscp::TReadSideAdmissionBoundaryId::from_raw(40),
        rscp::TReadSideAdmissionMode::passive_pull_from_bridge,
        rscp::TReadSideAdmissionStatus::ready,
        true,
        false
    };
    constexpr rscp::TReceiverContextDescriptor receiver{
        rscp::TReceiverContextId::from_raw(41),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };
    constexpr rscp::TPostBridgeBoundaryContractDescriptor missing_ack_contract{
        rscp::TPostBridgeBoundaryContractId::from_raw(42),
        rscp::TPostBridgeTransferSemantic::move,
        rscp::TPostBridgeBoundaryContractStatus::compatible,
        false,
        true
    };
    constexpr rscp::TReadSideCirculationProfile bad_read_profile{
        rscp::TReadSideProfileId::from_raw(43),
        rscp::TReadSideProfileStatus::ready,
        read_admission,
        receiver,
        missing_ack_contract
    };
    static_assert(!bad_read_profile.ready(),
        "Ack-required receiver must reject boundary without visible acknowledgement.");

    return 0;
}

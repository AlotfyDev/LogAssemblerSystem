#pragma once
#include <cstdint>
#include "TCapacityProfileId.hpp"
#include "TCapacityProfileStatus.hpp"
#include "TCapacityIssueKind.hpp"
#include "TCapacityValidationResult.hpp"

/*
    TDispatchCapacityProfile.hpp

    Responsibility:
        Defines production-grade pre-sized dispatch/output exposure capacity.

    Explicit non-ownership:
        Does not execute dispatch, bridge drain, or receiver acknowledgement.
*/
namespace assembler {
namespace circulation_mechanism {

struct TDispatchCapacityProfile final
{
    TCapacityProfileId profile_id{};
    TCapacityProfileStatus status{TCapacityProfileStatus::undefined};
    std::uint32_t max_envelopes_per_dispatch_round{0};
    std::uint32_t dispatch_waiting_list_capacity{0};
    std::uint32_t dispatch_reference_supply_depth{0};
    std::uint32_t passive_exposure_capacity{0};

    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (status == TCapacityProfileStatus::undefined || status == TCapacityProfileStatus::invalid) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (max_envelopes_per_dispatch_round == 0U) return rejected_capacity(TCapacityIssueKind::invalid_dispatch_capacity);
        if (dispatch_waiting_list_capacity == 0U) return rejected_capacity(TCapacityIssueKind::invalid_dispatch_capacity);
        if (dispatch_reference_supply_depth == 0U) return rejected_capacity(TCapacityIssueKind::reference_supply_depth_insufficient);
        if (passive_exposure_capacity == 0U) return rejected_capacity(TCapacityIssueKind::invalid_dispatch_capacity);
        if (dispatch_reference_supply_depth > dispatch_waiting_list_capacity) return rejected_capacity(TCapacityIssueKind::reference_supply_depth_insufficient);
        return accepted_capacity();
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

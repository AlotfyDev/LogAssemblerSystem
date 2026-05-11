#pragma once
#include <cstdint>
#include "TCapacityProfileId.hpp"
#include "TCapacityProfileStatus.hpp"
#include "TCapacityIssueKind.hpp"
#include "TCapacityValidationResult.hpp"

/*
    TIngressCapacityProfile.hpp

    Responsibility:
        Defines production-grade pre-sized intake capacity for ingress/container-providing.

    Explicit non-ownership:
        Does not perform placement or reference calculation.
*/
namespace assembler {
namespace circulation_mechanism {

struct TIngressCapacityProfile final
{
    TCapacityProfileId profile_id{};
    TCapacityProfileStatus status{TCapacityProfileStatus::undefined};
    std::uint32_t max_envelopes_per_ingress_round{0};
    std::uint32_t ingress_waiting_list_capacity{0};
    std::uint32_t ingress_reference_supply_depth{0};

    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (status == TCapacityProfileStatus::undefined || status == TCapacityProfileStatus::invalid) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (max_envelopes_per_ingress_round == 0U) return rejected_capacity(TCapacityIssueKind::invalid_ingress_capacity);
        if (ingress_waiting_list_capacity == 0U) return rejected_capacity(TCapacityIssueKind::invalid_ingress_capacity);
        if (ingress_reference_supply_depth == 0U) return rejected_capacity(TCapacityIssueKind::reference_supply_depth_insufficient);
        if (ingress_reference_supply_depth > ingress_waiting_list_capacity) return rejected_capacity(TCapacityIssueKind::reference_supply_depth_insufficient);
        return accepted_capacity();
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

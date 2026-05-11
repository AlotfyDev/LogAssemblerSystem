#pragma once
#include <cstdint>
#include <limits>
#include "TCapacityProfileId.hpp"
#include "TCapacityGenerationId.hpp"
#include "TCapacityProfileStatus.hpp"
#include "TUniformContainerCapacityProfile.hpp"
#include "TIngressCapacityProfile.hpp"
#include "TDispatchCapacityProfile.hpp"

/*
    TCirculationCapacityProfile.hpp

    Responsibility:
        Defines production-grade capacity envelope for one circulation engine profile.

    Production capabilities:
        - Validates uniform, ingress, and dispatch profiles together.
        - Computes total slots and total payload capacity units.
        - Validates total required ingress/dispatch capacity against available slots.
        - Declares extreme default and eviction flags.
        - Protects against overflow risk.

    Explicit non-ownership:
        - Does not allocate containers.
        - Does not execute scaling.
        - Does not handle runtime backpressure.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationCapacityProfile final
{
    TCapacityProfileId profile_id{};
    TCapacityGenerationId generation_id{};
    TCapacityProfileStatus status{TCapacityProfileStatus::undefined};
    TUniformContainerCapacityProfile uniform_container{};
    TIngressCapacityProfile ingress{};
    TDispatchCapacityProfile dispatch{};
    std::uint32_t container_count{0};
    bool extreme_default_enabled{false};
    bool eviction_enabled{false};

    [[nodiscard]] constexpr std::uint64_t total_slot_count() const noexcept
    {
        return static_cast<std::uint64_t>(container_count) * static_cast<std::uint64_t>(uniform_container.slots_per_container);
    }

    [[nodiscard]] constexpr std::uint64_t total_payload_capacity_units() const noexcept
    {
        return static_cast<std::uint64_t>(container_count) * uniform_container.total_units_per_container();
    }

    [[nodiscard]] constexpr bool total_multiplication_safe() const noexcept
    {
        return uniform_container.total_units_per_container() == 0U
            || container_count <= (std::numeric_limits<std::uint64_t>::max() / uniform_container.total_units_per_container());
    }

    [[nodiscard]] constexpr bool can_cover_ingress_round() const noexcept
    {
        return total_slot_count() >= ingress.max_envelopes_per_ingress_round;
    }

    [[nodiscard]] constexpr bool can_cover_dispatch_round() const noexcept
    {
        return total_slot_count() >= dispatch.max_envelopes_per_dispatch_round;
    }

    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (!generation_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_generation_id);
        if (status == TCapacityProfileStatus::undefined || status == TCapacityProfileStatus::invalid) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (container_count == 0U) return rejected_capacity(TCapacityIssueKind::invalid_container_count);
        if (!uniform_container.validate().accepted) return uniform_container.validate();
        if (!ingress.validate().accepted) return ingress.validate();
        if (!dispatch.validate().accepted) return dispatch.validate();
        if (!total_multiplication_safe()) return rejected_capacity(TCapacityIssueKind::overflow_risk);
        if (!can_cover_ingress_round()) return rejected_capacity(TCapacityIssueKind::invalid_ingress_capacity);
        if (!can_cover_dispatch_round()) return rejected_capacity(TCapacityIssueKind::invalid_dispatch_capacity);
        return accepted_capacity();
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

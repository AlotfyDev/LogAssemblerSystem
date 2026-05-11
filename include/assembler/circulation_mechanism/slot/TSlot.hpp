#pragma once

#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/state/TSlotState.hpp"
#include "TSlotAccessResult.hpp"
#include "TSlotOccupancyView.hpp"
#include "TSlotView.hpp"
#include "TSlotTransitionReport.hpp"

#include <array>
#include <cstdint>
#include <cstddef>

/*
    TSlot.hpp

    Delivery:
        CME-SLOT-PROD-W01 — Production Residency And Access Contract

    Current responsibility:
        Defines a production-grade fixed-capacity slot capable of hosting an
        opaque payload byte sequence under TSlotState transition rules.

    Production capabilities:
        - fixed-capacity local payload residency,
        - ingress reservation,
        - payload placement,
        - sealing,
        - dispatch readiness,
        - dispatch exposure,
        - release,
        - recycle to empty,
        - payload inspection as read-only bytes,
        - read-only slot view,
        - transition reports,
        - state-transition guarded mutation.

    Architectural role:
        Slot is a bounded placement/access structure inside a container. It is
        not an envelope, not a broker, not a dispatcher, and not a receiver.

    Explicit non-ownership:
        - Does not parse payload content.
        - Does not own envelope semantic lifecycle.
        - Does not decide container eligibility.
        - Does not calculate access references.
        - Does not execute bridge transfer.
        - Does not prove receiver delivery.
*/

namespace assembler {
namespace circulation_mechanism {


template <std::size_t CapacityBytes>
class TSlot final
{
public:
    static_assert(CapacityBytes > 0U, "TSlot capacity must be greater than zero.");

    static constexpr std::size_t k_capacity_bytes = CapacityBytes;

    constexpr explicit TSlot(TSlotIndex index) noexcept
        : index_(index)
    {
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return index_.is_valid();
    }

    [[nodiscard]] constexpr TSlotIndex index() const noexcept
    {
        return index_;
    }

    [[nodiscard]] constexpr TSlotState state() const noexcept
    {
        return state_;
    }

    [[nodiscard]] constexpr std::uint32_t payload_size() const noexcept
    {
        return payload_size_;
    }

    [[nodiscard]] constexpr bool occupied() const noexcept
    {
        return payload_size_ > 0U && is_resident(state_);
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return payload_size_ == 0U && state_ == TSlotState::empty;
    }

    [[nodiscard]] constexpr std::size_t capacity() const noexcept
    {
        return CapacityBytes;
    }

    [[nodiscard]] constexpr const std::array<std::uint8_t, CapacityBytes>& payload_buffer() const noexcept
    {
        return payload_;
    }

    [[nodiscard]] constexpr TSlotView view() const noexcept
    {
        return TSlotView{TSlotOccupancyView{index_, state_, occupied(), payload_size_}};
    }

    constexpr TSlotAccessResult reserve_for_ingress() noexcept
    {
        const auto before = state_;
        if (!is_valid()) return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_slot, before, state_};
        if (!can_transition(state_, TSlotState::reserved_for_ingress))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_transition, before, state_};
        }
        state_ = TSlotState::reserved_for_ingress;
        return TSlotAccessResult{TSlotAccessStatus::accepted, before, state_};
    }

    constexpr TSlotAccessResult place_payload(const std::uint8_t* data, std::uint32_t size) noexcept
    {
        const auto before = state_;
        if (!is_valid()) return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_slot, before, state_};
        if (data == nullptr || size == 0U || size > CapacityBytes)
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_empty_payload, before, state_};
        }
        if (!is_ingress_writable(state_))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_not_writable, before, state_};
        }
        if (!can_transition(state_, TSlotState::occupied))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_transition, before, state_};
        }

        for (std::uint32_t i = 0; i < size; ++i)
        {
            payload_[i] = data[i];
        }
        payload_size_ = size;
        state_ = TSlotState::occupied;
        return TSlotAccessResult{TSlotAccessStatus::accepted, before, state_};
    }

    constexpr TSlotAccessResult seal() noexcept
    {
        return transition_to(TSlotState::sealed);
    }

    constexpr TSlotAccessResult mark_dispatch_ready() noexcept
    {
        return transition_to(TSlotState::dispatch_ready);
    }

    constexpr TSlotAccessResult expose_for_dispatch() noexcept
    {
        if (payload_size_ == 0U)
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_no_payload_resident, state_, state_};
        }
        if (!is_dispatch_ready(state_))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_not_dispatch_ready, state_, state_};
        }
        return transition_to(TSlotState::dispatch_exposed);
    }

    constexpr TSlotAccessResult release() noexcept
    {
        const auto before = state_;
        if (payload_size_ == 0U && state_ != TSlotState::dispatch_exposed && state_ != TSlotState::dispatch_ready && state_ != TSlotState::sealed && state_ != TSlotState::occupied)
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_no_payload_resident, before, state_};
        }
        if (!can_transition(state_, TSlotState::released))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_transition, before, state_};
        }
        state_ = TSlotState::released;
        payload_size_ = 0U;
        clear_payload();
        return TSlotAccessResult{TSlotAccessStatus::accepted, before, state_};
    }

    constexpr TSlotAccessResult mark_recyclable() noexcept
    {
        return transition_to(TSlotState::recyclable);
    }

    constexpr TSlotAccessResult recycle_to_empty() noexcept
    {
        const auto before = state_;
        if (!can_transition(state_, TSlotState::empty))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_transition, before, state_};
        }
        state_ = TSlotState::empty;
        payload_size_ = 0U;
        clear_payload();
        return TSlotAccessResult{TSlotAccessStatus::accepted, before, state_};
    }

    [[nodiscard]] constexpr TSlotTransitionReport report_from(TSlotAccessResult result, std::uint32_t before_size) const noexcept
    {
        return TSlotTransitionReport{index_, result.before, result.after, result.status, before_size, payload_size_};
    }

private:
    constexpr TSlotAccessResult transition_to(TSlotState next_state) noexcept
    {
        const auto before = state_;
        if (!is_valid()) return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_slot, before, state_};
        if (!can_transition(state_, next_state))
        {
            return TSlotAccessResult{TSlotAccessStatus::rejected_invalid_transition, before, state_};
        }
        state_ = next_state;
        return TSlotAccessResult{TSlotAccessStatus::accepted, before, state_};
    }

    constexpr void clear_payload() noexcept
    {
        for (auto& byte : payload_)
        {
            byte = 0U;
        }
    }

    TSlotIndex index_{TSlotIndex::invalid()};
    TSlotState state_{TSlotState::empty};
    std::array<std::uint8_t, CapacityBytes> payload_{};
    std::uint32_t payload_size_{0};
};

} // namespace circulation_mechanism
} // namespace assembler

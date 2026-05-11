#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/state/TSlotState.hpp"
namespace assembler {
namespace circulation_mechanism {

template <std::size_t CapacityBytes>
class TSlot final {
public:
    static_assert(CapacityBytes > 0U, "slot capacity > 0");
    constexpr explicit TSlot(TSlotIndex index = TSlotIndex::invalid()) noexcept : index_(index) {}
    [[nodiscard]] constexpr bool is_valid() const noexcept { return index_.is_valid(); }
    [[nodiscard]] constexpr TSlotIndex index() const noexcept { return index_; }
    [[nodiscard]] constexpr TSlotState state() const noexcept { return state_; }
    [[nodiscard]] constexpr bool occupied() const noexcept { return size_ > 0U && is_resident(state_); }
    [[nodiscard]] constexpr std::uint32_t payload_size() const noexcept { return size_; }
    [[nodiscard]] constexpr std::size_t capacity() const noexcept { return CapacityBytes; }
    constexpr bool place_payload(const std::uint8_t* data, std::uint32_t size) noexcept {
        if (!is_valid() || !data || size == 0U || size > CapacityBytes) return false;
        if (!(state_ == TSlotState::empty || state_ == TSlotState::reserved_for_ingress)) return false;
        for (std::uint32_t i=0; i<size; ++i) payload_[i] = data[i];
        size_ = size;
        state_ = TSlotState::occupied;
        return true;
    }
    constexpr bool seal() noexcept { if (state_ != TSlotState::occupied) return false; state_ = TSlotState::sealed; return true; }
    constexpr bool mark_dispatch_ready() noexcept { if (state_ != TSlotState::sealed) return false; state_ = TSlotState::dispatch_ready; return true; }
    constexpr bool expose() noexcept { if (!occupied() || !is_dispatch_ready(state_)) return false; state_ = TSlotState::dispatch_exposed; return true; }
    constexpr bool release() noexcept { if (!occupied() && state_ != TSlotState::dispatch_exposed) return false; size_=0; clear(); state_=TSlotState::released; return true; }
    constexpr bool recycle_to_empty() noexcept { if (!(state_ == TSlotState::released || state_ == TSlotState::recyclable)) return false; size_=0; clear(); state_=TSlotState::empty; return true; }
private:
    constexpr void clear() noexcept { for (auto& b: payload_) b = 0U; }
    TSlotIndex index_;
    TSlotState state_{TSlotState::empty};
    std::array<std::uint8_t, CapacityBytes> payload_{};
    std::uint32_t size_{0};
};
} // namespace circulation_mechanism
} // namespace assembler

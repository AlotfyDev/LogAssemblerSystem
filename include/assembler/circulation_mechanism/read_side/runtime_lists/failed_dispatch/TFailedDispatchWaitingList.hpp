#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "assembler/circulation_mechanism/read_side_circulation_profile/failed_dispatch/TFailedDispatchRecord.hpp"
#include "assembler/circulation_mechanism/read_side/runtime_lists/TReadSideListOperationResult.hpp"

/*
    TFailedDispatchWaitingList.hpp

    Delivery:
        CME-READSIDE-PROD-W02 — FailedDispatch Retry DelayedRelease Runtime Lists

    Current responsibility:
        Fixed-capacity runtime list for read-side failed-dispatch records.

    Production capabilities:
        - stores failed-dispatch records,
        - rejects invalid records,
        - rejects duplicates,
        - supports lookup by TFailedDispatchId,
        - supports pop-front for retry,
        - preserves FIFO order,
        - does not store raw payloads.

    Explicit non-ownership:
        - Does not retry by itself.
        - Does not call bridge or receiver.
        - Does not persist records.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

template <std::size_t Capacity>
class TFailedDispatchWaitingList final {
public:
    static_assert(Capacity > 0U, "Capacity must be greater than zero.");

    [[nodiscard]] constexpr std::uint32_t size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ >= Capacity; }

    [[nodiscard]] constexpr const read_side_circulation_profile::TFailedDispatchRecord* try_find(read_side_circulation_profile::TFailedDispatchId id) const noexcept {
        for (std::uint32_t i = 0; i < size_; ++i) {
            if (records_[i].failed_dispatch_id == id) return &records_[i];
        }
        return nullptr;
    }

    constexpr TReadSideListOperationResult push(read_side_circulation_profile::TFailedDispatchRecord record) noexcept {
        if (!record.is_valid()) return {TReadSideListStatus::rejected_invalid_record, size_};
        if ((record.state == read_side_circulation_profile::TFailedDispatchState::resolved || record.state == read_side_circulation_profile::TFailedDispatchState::abandoned || record.state == read_side_circulation_profile::TFailedDispatchState::delegated || record.state == read_side_circulation_profile::TFailedDispatchState::faulted)) return {TReadSideListStatus::rejected_terminal, size_};
        if (try_find(record.failed_dispatch_id)) return {TReadSideListStatus::rejected_duplicate, size_};
        if (full()) return {TReadSideListStatus::rejected_full, size_};
        records_[size_++] = record;
        return {TReadSideListStatus::accepted, size_};
    }

    [[nodiscard]] constexpr const read_side_circulation_profile::TFailedDispatchRecord* front() const noexcept {
        return size_ > 0U ? &records_[0] : nullptr;
    }

    constexpr TReadSideListOperationResult pop_front() noexcept {
        if (empty()) return {TReadSideListStatus::rejected_empty, size_};
        for (std::uint32_t i = 1; i < size_; ++i) {
            records_[i - 1] = records_[i];
        }
        --size_;
        return {TReadSideListStatus::accepted, size_};
    }

private:
    std::array<read_side_circulation_profile::TFailedDispatchRecord, Capacity> records_{};
    std::uint32_t size_{0};
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

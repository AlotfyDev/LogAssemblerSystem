#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "assembler/circulation_mechanism/read_side_circulation_profile/delayed_release/TDelayedReleaseRecord.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/delayed_release/TDelayedReleaseProfile.hpp"
#include "assembler/circulation_mechanism/read_side/runtime_lists/TReadSideListOperationResult.hpp"

/*
    TDelayedReleaseList.hpp

    Current responsibility:
        Fixed-capacity runtime list for delayed-release records.

    Production capabilities:
        - stores pending delayed-release records,
        - rejects invalid/non-pending records,
        - applies decision updates from delayed-release profile,
        - supports pop-front,
        - does not perform actual release.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

template <std::size_t Capacity>
class TDelayedReleaseList final {
public:
    static_assert(Capacity > 0U, "Capacity must be greater than zero.");

    [[nodiscard]] constexpr std::uint32_t size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ >= Capacity; }

    constexpr TReadSideListOperationResult push(read_side_circulation_profile::TDelayedReleaseRecord record) noexcept {
        if (!record.is_valid()) return {TReadSideListStatus::rejected_invalid_record, size_};
        if (!record.pending()) return {TReadSideListStatus::rejected_not_pending, size_};
        if (full()) return {TReadSideListStatus::rejected_full, size_};
        records_[size_++] = record;
        return {TReadSideListStatus::accepted, size_};
    }

    constexpr TReadSideListOperationResult apply_profile_to_front(read_side_circulation_profile::TDelayedReleaseProfile profile, bool trigger_observed) noexcept {
        if (empty()) return {TReadSideListStatus::rejected_empty, size_};
        auto decision = profile.decide(trigger_observed, records_[0].elapsed_ticks);
        records_[0].apply_decision(decision);
        return {TReadSideListStatus::accepted, size_};
    }

    [[nodiscard]] constexpr const read_side_circulation_profile::TDelayedReleaseRecord* front() const noexcept {
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
    std::array<read_side_circulation_profile::TDelayedReleaseRecord, Capacity> records_{};
    std::uint32_t size_{0};
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

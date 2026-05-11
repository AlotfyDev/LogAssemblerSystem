#pragma once
#include "TWaitingListEntry.hpp"
#include "TWaitingListAdmissionStatus.hpp"

/*
    TIngressWaitingListRegistrationReport.hpp

    Delivery:
        CME-WAITING-LIST-PROD-W01

    Responsibility:
        Evidence carrier for waiting-list admission.

    Non-ownership:
        Report does not mutate waiting-list or store payload.
*/
namespace assembler {
namespace circulation_mechanism {

struct TIngressWaitingListRegistrationReport final {
    TWaitingListEntry entry{};
    TWaitingListAdmissionStatus status{TWaitingListAdmissionStatus::not_attempted};
    std::uint32_t size_after{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return entry.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TWaitingListAdmissionStatus::accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler

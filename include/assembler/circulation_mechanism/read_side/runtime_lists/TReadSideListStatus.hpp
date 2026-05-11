#pragma once
#include <cstdint>
/*
    TReadSideListStatus.hpp

    Delivery:
        CME-READSIDE-PROD-W02 — FailedDispatch Retry DelayedRelease Runtime Lists

    Responsibility:
        Defines operational result/status for read-side runtime lists.

    Explicit non-ownership:
        Does not execute retry, receiver acknowledgement, or persistence.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

enum class TReadSideListStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_invalid_record,
    rejected_duplicate,
    rejected_full,
    rejected_empty,
    rejected_not_found,
    rejected_not_retryable,
    rejected_not_pending,
    rejected_terminal
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

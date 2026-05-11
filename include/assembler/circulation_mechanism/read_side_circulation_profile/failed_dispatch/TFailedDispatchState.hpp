#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TFailedDispatchState : std::uint8_t { none, recorded, queued_for_retry, retrying, resolved, abandoned, delegated, faulted };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

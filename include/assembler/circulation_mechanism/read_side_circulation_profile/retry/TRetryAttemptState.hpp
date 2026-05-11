#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TRetryAttemptState : std::uint8_t { not_started, scheduled, in_progress, succeeded, failed, exhausted, cancelled, blocked };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

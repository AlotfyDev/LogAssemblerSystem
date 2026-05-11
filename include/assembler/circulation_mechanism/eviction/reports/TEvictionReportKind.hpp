#pragma once
    #include <cstdint>
    /*
        TEvictionReportKind.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Eviction report kind.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TEvictionReportKind : std::uint8_t {
        selection, applied, rejected, delegated, unsafe_attempt, time_range_invalid, profile_insufficient
    };
    } // namespace circulation_mechanism
} // namespace assembler

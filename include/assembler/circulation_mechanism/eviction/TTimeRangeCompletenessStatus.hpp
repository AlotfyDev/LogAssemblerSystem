#pragma once
    #include <cstdint>
    /*
        TTimeRangeCompletenessStatus.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Completeness of container time range metadata.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TTimeRangeCompletenessStatus : std::uint8_t {
        empty, complete, partial, unknown, invalid
    };
    } // namespace circulation_mechanism
} // namespace assembler

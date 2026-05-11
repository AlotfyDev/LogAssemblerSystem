#pragma once
    #include <cstdint>
    /*
        TDispatchExposureStatus.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Output exposure lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatchExposureStatus : std::uint8_t {
        not_exposed, prepared, exposed, observed, consumed, expired, released, failed
    };
    } // namespace circulation_mechanism
} // namespace assembler

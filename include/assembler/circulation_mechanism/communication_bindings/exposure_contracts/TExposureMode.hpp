#pragma once
    #include <cstdint>
    /*
        TExposureMode.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Exposure mode.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TExposureMode : std::uint8_t {
        none, passive_pull, push, hybrid, notification_only
    };
    } // namespace circulation_mechanism
} // namespace assembler

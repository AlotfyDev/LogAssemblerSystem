#pragma once
    #include <cstdint>
    /*
        TReleaseKind.hpp
        Delivery: CME-RELEASE-RECYCLE-PROD-W01
        Responsibility: Classifies the release level.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TReleaseKind : std::uint8_t {
        slot_release, container_release, reference_release, exposure_release, round_release, registry_release
    };
    } // namespace circulation_mechanism
} // namespace assembler

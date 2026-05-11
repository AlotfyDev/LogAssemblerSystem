#pragma once
    #include <cstdint>
    /*
        TEvictionPolicyKind.hpp
        Delivery: CME-EVICTION-PROD-W01
        Responsibility: Eviction policy kinds.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TEvictionPolicyKind : std::uint8_t {
        no_eviction_pre_bridge, oldest_time_range, fifo_container, delegate_to_read_side, emergency
    };
    } // namespace circulation_mechanism
} // namespace assembler

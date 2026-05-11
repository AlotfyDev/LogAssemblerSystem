#pragma once
    #include <cstdint>

    /*
        TReadSideAdmissionMode.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines post-bridge admission mode.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideAdmissionMode : std::uint8_t {
        passive_pull_from_bridge,
        bridge_push_to_read_side,
        hybrid,
        diagnostic_only
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

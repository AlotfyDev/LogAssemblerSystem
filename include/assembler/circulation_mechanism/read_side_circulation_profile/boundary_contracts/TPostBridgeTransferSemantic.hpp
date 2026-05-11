#pragma once
    #include <cstdint>

    /*
        TPostBridgeTransferSemantic.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines post-bridge transfer semantic.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TPostBridgeTransferSemantic : std::uint8_t {
        unknown,
        copy,
        move,
        borrowed_view,
        exposure_only,
        implementation_defined
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

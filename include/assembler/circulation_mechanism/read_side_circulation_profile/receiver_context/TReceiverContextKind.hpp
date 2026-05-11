#pragma once
    #include <cstdint>

    /*
        TReceiverContextKind.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines receiver/addon context kind.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReceiverContextKind : std::uint8_t {
        unknown,
        in_process_receiver,
        database_adapter,
        file_sink,
        telemetry_adapter,
        diagnostic_sink,
        custom_addon
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

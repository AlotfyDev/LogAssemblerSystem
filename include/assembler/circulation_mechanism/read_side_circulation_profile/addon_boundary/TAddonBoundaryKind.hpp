#pragma once
    #include <cstdint>

    /*
        TAddonBoundaryKind.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Classifies addon boundary kind.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TAddonBoundaryKind : std::uint8_t {
        unknown, in_process_receiver, database_adapter, thin_c_abi_adapter, open_telemetry_adapter, file_sink_adapter, diagnostic_sink_adapter, custom
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler

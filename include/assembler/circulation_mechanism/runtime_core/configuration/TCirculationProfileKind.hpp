#pragma once
    #include <cstdint>

    /*
        TCirculationProfileKind.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Profile kind classification without binding a concrete subsystem runtime.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationProfileKind : std::uint8_t {
        shared_core,
        pre_bridge,
        read_side,
        diagnostic_only,
        test
    };
    } // namespace circulation_mechanism
} // namespace assembler

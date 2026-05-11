#pragma once
    #include <cstdint>

    /*
        TCirculationConfigurationStatus.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Shared configuration status vocabulary.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationConfigurationStatus : std::uint8_t {
        undefined,
        draft,
        validated,
        active,
        rejected,
        deprecated,
        invalid
    };
    } // namespace circulation_mechanism
} // namespace assembler

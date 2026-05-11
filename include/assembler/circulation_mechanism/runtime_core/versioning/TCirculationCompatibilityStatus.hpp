#pragma once
    #include <cstdint>

    /*
        TCirculationCompatibilityStatus.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Version/profile compatibility status.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationCompatibilityStatus : std::uint8_t {
        unknown,
        compatible,
        incompatible,
        requires_migration,
        deprecated_compatible,
        blocked
    };
    } // namespace circulation_mechanism
} // namespace assembler

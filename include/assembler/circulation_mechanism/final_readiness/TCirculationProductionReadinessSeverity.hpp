#pragma once
    #include <cstdint>

    /*
        TCirculationProductionReadinessSeverity.hpp

        Delivery:
            CME-PROD-HARDEN-W08 — Final Production Readiness Gate

        Responsibility:
            Classifies final production readiness severity.

        Explicit non-ownership:
            - Does not execute runtime.
            - Does not deploy or persist reports by itself.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

    enum class TCirculationProductionReadinessSeverity : std::uint8_t {
        info, warning, error, critical
    };
    } // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

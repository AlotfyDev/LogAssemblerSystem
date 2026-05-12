#pragma once
    #include <cstdint>

    /*
        TCirculationProductionReadinessStatus.hpp

        Delivery:
            CME-PROD-HARDEN-W08 — Final Production Readiness Gate

        Responsibility:
            Classifies final production readiness status.

        Explicit non-ownership:
            - Does not execute runtime.
            - Does not deploy or persist reports by itself.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

    enum class TCirculationProductionReadinessStatus : std::uint8_t {
        not_evaluated, passed, failed, blocked, deferred
    };
    } // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler

#pragma once
    #include <cstdint>

    /*
        TProductionReadinessSeverity.hpp

        Delivery:
            CME-INTEGRATION-PROD-W04 — Production Readiness Gate

        Responsibility:
            Classifies readiness issue severity.

        Explicit non-ownership:
            - Does not execute runtime circulation.
            - Does not mutate components.
            - Does not replace tests.
            - Does not certify external bridge/receiver/addon runtime.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TProductionReadinessSeverity : std::uint8_t {
        info, warning, error, critical
    };
    } // namespace circulation_mechanism
} // namespace assembler

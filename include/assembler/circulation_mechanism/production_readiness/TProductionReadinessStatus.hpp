#pragma once
    #include <cstdint>

    /*
        TProductionReadinessStatus.hpp

        Delivery:
            CME-INTEGRATION-PROD-W04 — Production Readiness Gate

        Responsibility:
            Classifies readiness gate status.

        Explicit non-ownership:
            - Does not execute runtime circulation.
            - Does not mutate components.
            - Does not replace tests.
            - Does not certify external bridge/receiver/addon runtime.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TProductionReadinessStatus : std::uint8_t {
        not_evaluated, passed, failed, blocked, deferred
    };
    } // namespace circulation_mechanism
} // namespace assembler

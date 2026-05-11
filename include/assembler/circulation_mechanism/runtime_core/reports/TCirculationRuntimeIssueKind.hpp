#pragma once
    #include <cstdint>

    /*
        TCirculationRuntimeIssueKind.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Shared runtime issue classification.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationRuntimeIssueKind : std::uint8_t {
        none,
        invalid_runtime_id,
        invalid_lifecycle_transition,
        configuration_missing,
        configuration_invalid,
        version_incompatible,
        subsystem_not_bound,
        unknown
    };
    } // namespace circulation_mechanism
} // namespace assembler

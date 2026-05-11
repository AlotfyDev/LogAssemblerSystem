#pragma once
    #include <cstdint>

    /*
        TCirculationConfigurationIssueKind.hpp

        Delivery:
            CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

        Responsibility:
            Shared configuration issue classification.

        Explicit non-ownership:
            - Does not execute component behavior.
            - Does not perform bridge/receiver runtime.
            - Does not own concrete subsystem facade.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCirculationConfigurationIssueKind : std::uint8_t {
        none,
        invalid_configuration_id,
        invalid_version,
        missing_profile_kind,
        profile_not_validated,
        incompatible_api_version,
        incompatible_profile_version,
        unsupported_profile_kind,
        unknown
    };
    } // namespace circulation_mechanism
} // namespace assembler

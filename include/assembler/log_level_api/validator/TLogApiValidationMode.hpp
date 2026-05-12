#pragma once

/*
    LOGAPI-W03 — Validator Contract And Binding Surface

    Responsibility:
        Define validation contracts, validation result carriers, validation issues,
        validator capabilities, safe points, and configuration-time validator
        binding descriptors.

    Boundary:
        No concrete validators, concrete schemas, metadata structs, timestamp
        algorithms, envelope assembly, API hot path, communication bindings,
        or policy assignment.

    Doctrine:
        Validator contracts are core.
        Concrete validators are schema-family add-ons.
        Validator binding is resolved before the hot path.
*/

namespace assembler::log_level_api::validator {

enum class TLogApiValidationMode {
    Unknown = 0,
    None,
    Structural,
    Strict,
    Advisory
};

} // namespace assembler::log_level_api::validator

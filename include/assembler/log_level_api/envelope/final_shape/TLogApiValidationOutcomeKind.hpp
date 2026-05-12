#pragma once

/*
    LOGAPI-W23 — Envelope Final Shape And Identity

    Responsibility:
        Define final envelope identity/header shape, official envelope slots,
        validation result slot, readiness view, and final envelope carrier.

    Boundary:
        The envelope is a carrier and identity surface, not an assembler and not
        a policy decision maker. A validation result slot records valid/invalid
        evidence, but accepting or rejecting a payload based on that result is a
        separate user/policy concern.

    Doctrine:
        Envelope = identity/header + content slot + metadata slot + timestamp slot
                   + validation result slot.
*/

namespace assembler::log_level_api::envelope::final_shape {

enum class TLogApiValidationOutcomeKind {
    Unknown = 0,
    NotEvaluated,
    Valid,
    Invalid
};

} // namespace assembler::log_level_api::envelope::final_shape

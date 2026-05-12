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

#include "TLogApiEnvelopeContentSlot.hpp"
#include "TLogApiEnvelopeHeaderFinal.hpp"
#include "TLogApiEnvelopeIdentityFactory.hpp"
#include "TLogApiEnvelopeMetadataSlot.hpp"
#include "TLogApiEnvelopeReadinessKind.hpp"
#include "TLogApiEnvelopeReadinessView.hpp"
#include "TLogApiEnvelopeSlotKind.hpp"
#include "TLogApiEnvelopeTimestampSlot.hpp"
#include "TLogApiEnvelopeValidationResultSlot.hpp"
#include "TLogApiEnvelopeVersion.hpp"
#include "TLogApiFinalEnvelope.hpp"
#include "TLogApiFinalEnvelopeId.hpp"
#include "TLogApiFinalEnvelopeIssue.hpp"
#include "TLogApiFinalEnvelopeResult.hpp"
#include "TLogApiFinalEnvelopeStatus.hpp"
#include "TLogApiValidationOutcomeKind.hpp"

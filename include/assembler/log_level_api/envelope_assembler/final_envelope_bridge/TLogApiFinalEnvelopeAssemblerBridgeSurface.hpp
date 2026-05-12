#pragma once

/*
    LOGAPI-EXT-W02 — Final Envelope Assembler Bridge

    Responsibility:
        Bridge the W08 envelope assembler family inputs/profiles into the W23
        final envelope shape, producing TLogApiFinalEnvelopeResult.

    Boundary:
        This wave does not implement new parser behavior, metadata injection,
        timestamp stabilization, circulation handoff, policy assignment, bridge
        orchestration, or receiver behavior.

    Doctrine:
        W08 assembly profile remains the assembler-family selection surface.
        W23 final envelope remains the target carrier shape.
        Validation result slot remains evidence only; it does not decide payload
        acceptance or rejection.
*/

#include "TLogApiDefaultFinalEnvelopeAssemblerBridgeProfile.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeId.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeIssue.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeProfile.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeStatus.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeView.hpp"
#include "TLogApiFinalEnvelopeAssemblyBridgeDetail.hpp"
#include "TLogApiFinalEnvelopeAssemblyBridgeInput.hpp"
#include "TLogApiFinalEnvelopeAssemblyBridgeResult.hpp"
#include "TLogApiPlainFinalEnvelopeAssemblerBridge.hpp"
#include "TLogApiValidatorComposedFinalEnvelopeAssemblerBridge.hpp"

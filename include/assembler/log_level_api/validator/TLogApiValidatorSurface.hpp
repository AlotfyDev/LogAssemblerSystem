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

#include "TLogApiValidationIssue.hpp"
#include "TLogApiValidationMode.hpp"
#include "TLogApiValidationRequest.hpp"
#include "TLogApiValidationResult.hpp"
#include "TLogApiValidationSeverity.hpp"
#include "TLogApiValidatorBindingDescriptor.hpp"
#include "TLogApiValidatorBindingRegistryView.hpp"
#include "TLogApiValidatorBindingResolver.hpp"
#include "TLogApiValidatorBindingView.hpp"
#include "TLogApiValidatorCapabilityKind.hpp"
#include "TLogApiValidatorCapabilitySet.hpp"
#include "TLogApiValidatorContract.hpp"
#include "TLogApiValidatorId.hpp"
#include "TLogApiValidatorSafePointKind.hpp"
#include "TLogApiValidatorSafePointSet.hpp"
#include "TLogApiValidatorStatus.hpp"

#pragma once

/*
    circulation_mechanism_w08.hpp

    Convenience include for CME-W08 reference handles and validity model.
    This header does not implement ReferencePrecalculator behavior.
*/

#include "reference_precalculator/handles/TAccessRefId.hpp"
#include "reference_precalculator/handles/TAccessRefDirection.hpp"
#include "reference_precalculator/handles/TAccessRefKind.hpp"
#include "reference_precalculator/handles/TAccessRefScope.hpp"
#include "reference_precalculator/handles/TSlotAccessRef.hpp"
#include "reference_precalculator/handles/TIngressAccessRef.hpp"
#include "reference_precalculator/handles/TDispatchAccessRef.hpp"
#include "reference_precalculator/handles/TRoundScopedRef.hpp"
#include "reference_precalculator/handles/TNextRefToken.hpp"

#include "reference_precalculator/validity/TReferenceValidityDecisionKind.hpp"
#include "reference_precalculator/validity/TReferenceValidityPolicy.hpp"
#include "reference_precalculator/validity/TStaleReferenceReport.hpp"
#include "reference_precalculator/validity/TReferenceInvalidationReport.hpp"
#include "reference_precalculator/validity/TReferenceDirectionMismatchReport.hpp"

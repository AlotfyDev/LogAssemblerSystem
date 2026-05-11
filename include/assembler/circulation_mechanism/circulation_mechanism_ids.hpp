#pragma once

/*
    circulation_mechanism_ids.hpp

    Delivery:
        CME-IDS-PROD-W01 — Production Identity Contract

    Responsibility:
        Aggregate include for production-grade CME identity atoms.

    Non-ownership:
        This aggregate does not create a facade or runtime component.
*/

#include "ids/TBoundaryId.hpp"
#include "ids/TContainerId.hpp"
#include "ids/TContainerRegistryIndex.hpp"
#include "ids/TReferenceId.hpp"
#include "ids/TRoundId.hpp"
#include "ids/TSlotIndex.hpp"
#include "ids/TIdentityAtomTraits.hpp"

#pragma once

/*
    LOGAPI-W06 — API Facade Content-Only Input

    This header belongs to the Log Level API consuming facade layer.

    Responsibility:
        Define the content-only API input surface and admission result carriers
        that consume a previously resolved active profile.

    Boundary:
        The API facade receives content only.
        It must not receive schema definitions, metadata struct definitions,
        validator bindings, timestamp stabilization rules, envelope assembly
        instructions, communication bindings, or policy assignment material with
        every payload.

    Doctrine:
        Configure first. Consume content only.
        The API facade uses an already resolved active profile.
*/

#include "TLogApiContentInputStatus.hpp"
#include "TLogApiContentOnlyInput.hpp"
#include "TLogApiFacade.hpp"
#include "TLogApiFacadeAcceptedContent.hpp"
#include "TLogApiFacadeAdmission.hpp"
#include "TLogApiFacadeConfigRef.hpp"
#include "TLogApiFacadeId.hpp"
#include "TLogApiFacadeInputResult.hpp"
#include "TLogApiFacadeIssue.hpp"
#include "TLogApiFacadeStatus.hpp"
#include "TLogApiFacadeView.hpp"

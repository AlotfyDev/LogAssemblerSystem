#pragma once

/*
    LOGAPI-W02 — Content Profile And Schema Paths

    This header belongs to the Log Level API content-profile layer.

    Responsibility:
        Define content profile abstractions and schema path descriptors used by
        the configuration surface before the consuming hot path receives content.

    Boundary:
        This file must not define concrete JSON schemas, concrete C-style struct
        layouts, concrete validators, metadata struct implementation, timestamp
        stabilization algorithms, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Content schema paths are open and configurable.
        JSON and C-style struct primitive paths are separated.
        The consuming API receives content only and uses an already resolved
        active profile.
*/

#include "TLogApiCStyleStructPrimitiveProfileDescriptor.hpp"
#include "TLogApiContentInputRef.hpp"
#include "TLogApiContentProfileDescriptor.hpp"
#include "TLogApiContentProfileId.hpp"
#include "TLogApiContentProfileRegistryView.hpp"
#include "TLogApiContentProfileResolver.hpp"
#include "TLogApiContentProfileStatus.hpp"
#include "TLogApiContentProfileView.hpp"
#include "TLogApiContentSchemaPathDescriptor.hpp"
#include "TLogApiContentSchemaPathStatus.hpp"
#include "TLogApiJsonContentProfileDescriptor.hpp"

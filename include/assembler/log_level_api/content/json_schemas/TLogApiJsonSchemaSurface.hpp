#pragma once

/*
    LOGAPI-W10 — Default JSON Content Schemas

    This header belongs to the default JSON content schema add-on pack.

    Responsibility:
        Define default JSON content schema descriptors, JSON field descriptors,
        required field sets, default field values, and level-specific default
        JSON schema profiles.

    Boundary:
        This wave defines JSON schema descriptors only.
        It must not implement concrete JSON parsing, concrete validators, metadata
        structs, timestamp stabilization, envelope assembly, API facade hot-path
        behavior, circulation bindings, or policy assignment.

    Doctrine:
        Default JSON schemas are bundled conveniences, not a closed content universe.
        The consuming API still receives content only.
*/

#include "TLogApiDefaultJsonSchemaFactory.hpp"
#include "TLogApiDefaultJsonSchemaPack.hpp"
#include "TLogApiJsonDefaultValue.hpp"
#include "TLogApiJsonFieldDescriptor.hpp"
#include "TLogApiJsonFieldId.hpp"
#include "TLogApiJsonFieldPresenceKind.hpp"
#include "TLogApiJsonFieldSet.hpp"
#include "TLogApiJsonFieldValueKind.hpp"
#include "TLogApiJsonLevelSchemaDescriptor.hpp"
#include "TLogApiJsonLevelSchemaView.hpp"
#include "TLogApiJsonSchemaId.hpp"
#include "TLogApiJsonSchemaIssue.hpp"
#include "TLogApiJsonSchemaPackId.hpp"
#include "TLogApiJsonSchemaPackView.hpp"
#include "TLogApiJsonSchemaRegistrationReport.hpp"
#include "TLogApiJsonSchemaValidationInputDescriptor.hpp"
#include "TLogApiJsonUnknownFieldPolicy.hpp"
#include "TLogApiLogLevelKind.hpp"

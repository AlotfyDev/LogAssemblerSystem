#pragma once

/*
    LOGAPI-W11 — Default C-Style Struct Primitive Schemas

    This header belongs to the default C-style struct primitive content schema
    add-on pack.

    Responsibility:
        Define ABI/layout-sensitive primitive struct schema descriptors,
        fixed-width primitive field descriptors, explicit offsets, sizes,
        alignment, padding, endianness, presence/default flags, and level-specific
        primitive struct schema profiles.

    Boundary:
        This wave defines C-style struct primitive schema descriptors only.
        It must not implement binary parsing, concrete validators, metadata structs,
        timestamp stabilization, envelope assembly, API facade hot-path behavior,
        circulation bindings, or policy assignment.

    Doctrine:
        C-style struct schemas must be layout-specified, not compiler-implied.
        Defaults are bundled conveniences, not a closed content universe.
*/

#include "TLogApiCStructCrossLanguageNote.hpp"
#include "TLogApiCStructDefaultValue.hpp"
#include "TLogApiCStructEndianKind.hpp"
#include "TLogApiCStructFieldDescriptor.hpp"
#include "TLogApiCStructFieldId.hpp"
#include "TLogApiCStructFieldLayout.hpp"
#include "TLogApiCStructFieldPresenceKind.hpp"
#include "TLogApiCStructLevelSchemaDescriptor.hpp"
#include "TLogApiCStructLevelSchemaView.hpp"
#include "TLogApiCStructLogLevelKind.hpp"
#include "TLogApiCStructPrimitiveKind.hpp"
#include "TLogApiCStructSchemaId.hpp"
#include "TLogApiCStructSchemaIssue.hpp"
#include "TLogApiCStructSchemaPackId.hpp"
#include "TLogApiCStructSchemaPackView.hpp"
#include "TLogApiCStructSchemaRegistrationReport.hpp"
#include "TLogApiCStructValidationInputDescriptor.hpp"
#include "TLogApiDefaultCStructSchemaFactory.hpp"
#include "TLogApiDefaultCStructSchemaPack.hpp"

#pragma once

/*
    LOGAPI-W04 — Metadata Struct And Field Values

    This header belongs to the Log Level API metadata struct and field value layer.

    Responsibility:
        Define metadata struct descriptors, metadata fields, mutable metadata
        values, update sets, prepared metadata blocks, and metadata injector
        configuration surfaces.

    Boundary:
        Metadata is not content.
        Metadata is not stabilized timestamp.
        Metadata does not define content schema fields, required/default validator
        inputs, concrete validators, timestamp stabilization algorithms, envelope
        assembly, communication bindings, or policy assignment.

    Doctrine:
        Content + metadata struct + stabilized timestamp meet later inside the
        envelope through the envelope assembler.
*/

#include "TLogApiDefaultMetadataProfile.hpp"
#include "TLogApiMetadataFieldDescriptor.hpp"
#include "TLogApiMetadataFieldId.hpp"
#include "TLogApiMetadataFieldSet.hpp"
#include "TLogApiMetadataFieldValue.hpp"
#include "TLogApiMetadataFieldValueKind.hpp"
#include "TLogApiMetadataInjectionIssue.hpp"
#include "TLogApiMetadataInjectionResult.hpp"
#include "TLogApiMetadataInjector.hpp"
#include "TLogApiMetadataInjectorConfig.hpp"
#include "TLogApiMetadataStructDescriptor.hpp"
#include "TLogApiMetadataStructId.hpp"
#include "TLogApiMetadataStructStatus.hpp"
#include "TLogApiMetadataStructView.hpp"
#include "TLogApiMetadataUpdateSet.hpp"
#include "TLogApiMetadataValueSet.hpp"
#include "TLogApiPreparedMetadataBlock.hpp"

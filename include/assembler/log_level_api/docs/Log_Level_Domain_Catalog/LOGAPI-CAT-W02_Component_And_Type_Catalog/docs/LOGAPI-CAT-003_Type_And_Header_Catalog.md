# LOGAPI-CAT-003 — Type And Header Catalog

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-003-DOC-001 | Document Title | Type And Header Catalog |
| LOGAPI-CAT-003-DOC-002 | File Name | `LOGAPI-CAT-003_Type_And_Header_Catalog.md` |
| LOGAPI-CAT-003-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-003-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-003-DOC-005 | Scope Level | Type catalog, header catalog, implementation wave map |
| LOGAPI-CAT-003-DOC-006 | Status | Type Catalog Draft |
| LOGAPI-CAT-003-DOC-007 | Previous Document | `LOGAPI-CAT-002_Component_Inventory_And_Responsibilities.md` |
| LOGAPI-CAT-003-DOC-008 | Related Implementation Waves | `LOGAPI-W01` through `LOGAPI-W34` |

---

## 2. Purpose

This document provides a wave-by-wave type and header catalog for Log Level API.

The goal is to make the implementation surface searchable by concern and to support future cleanup, consolidation, and extension.

---

## 3. Type/Header Catalog By Wave

## 3.1 W01 — Configuration Surface And Default Profile

Folder:

```text
include/assembler/log_level_api/api_configurator/
```

Primary headers:

```text
TLogApiConfigurationId.hpp
TLogApiConfigurationStatus.hpp
TLogApiSchemaPathKind.hpp
TLogApiAssemblerFamilyKind.hpp
TLogApiConfigurationIssue.hpp
TLogApiConfigurationPatch.hpp
TLogApiDefaultConfiguration.hpp
TLogApiActiveProfile.hpp
TLogApiConfigurationResult.hpp
TLogApiConfigurationView.hpp
TLogApiConfigurator.hpp
TLogApiConfigurationSurface.hpp
```

Core types:

```text
TLogApiDefaultConfiguration
TLogApiActiveProfile
TLogApiConfigurator
```

---

## 3.2 W02 — Content Profile And Schema Paths

Folder:

```text
include/assembler/log_level_api/content/
```

Primary headers:

```text
TLogApiContentProfileId.hpp
TLogApiContentProfileStatus.hpp
TLogApiContentSchemaPathStatus.hpp
TLogApiContentSchemaPathDescriptor.hpp
TLogApiJsonContentProfileDescriptor.hpp
TLogApiCStyleStructPrimitiveProfileDescriptor.hpp
TLogApiContentProfileDescriptor.hpp
TLogApiContentProfileRegistryView.hpp
TLogApiContentInputRef.hpp
TLogApiContentProfileView.hpp
TLogApiContentProfileResolver.hpp
TLogApiContentProfileSurface.hpp
```

Core types:

```text
TLogApiContentProfileDescriptor
TLogApiContentInputRef
TLogApiContentProfileRegistryView
```

---

## 3.3 W03 — Validator Contract And Binding Surface

Folder:

```text
include/assembler/log_level_api/validator/
```

Primary headers:

```text
TLogApiValidatorId.hpp
TLogApiValidatorStatus.hpp
TLogApiValidationMode.hpp
TLogApiValidationSeverity.hpp
TLogApiValidatorCapabilityKind.hpp
TLogApiValidatorSafePointKind.hpp
TLogApiValidationIssue.hpp
TLogApiValidationResult.hpp
TLogApiValidatorCapabilitySet.hpp
TLogApiValidatorSafePointSet.hpp
TLogApiValidatorContract.hpp
TLogApiValidatorBindingDescriptor.hpp
TLogApiValidatorBindingView.hpp
TLogApiValidatorBindingRegistryView.hpp
TLogApiValidatorBindingResolver.hpp
TLogApiValidationRequest.hpp
TLogApiValidatorSurface.hpp
```

Core types:

```text
TLogApiValidationResult
TLogApiValidatorContract
TLogApiValidatorBindingDescriptor
```

---

## 3.4 W04 — Metadata Struct And Field Values

Folder:

```text
include/assembler/log_level_api/metadata_injector/
```

Primary headers:

```text
TLogApiMetadataStructId.hpp
TLogApiMetadataFieldId.hpp
TLogApiMetadataStructStatus.hpp
TLogApiMetadataFieldValueKind.hpp
TLogApiMetadataFieldDescriptor.hpp
TLogApiMetadataFieldValue.hpp
TLogApiMetadataStructDescriptor.hpp
TLogApiMetadataFieldSet.hpp
TLogApiMetadataValueSet.hpp
TLogApiMetadataUpdateSet.hpp
TLogApiPreparedMetadataBlock.hpp
TLogApiMetadataInjectorConfig.hpp
TLogApiMetadataInjectionIssue.hpp
TLogApiMetadataInjectionResult.hpp
TLogApiMetadataStructView.hpp
TLogApiMetadataInjector.hpp
TLogApiDefaultMetadataProfile.hpp
TLogApiMetadataSurface.hpp
```

Core types:

```text
TLogApiMetadataStructDescriptor
TLogApiMetadataFieldValue
TLogApiPreparedMetadataBlock
TLogApiMetadataInjectorConfig
```

---

## 3.5 W05 — Timestamp Stabilizer Config And Model

Folder:

```text
include/assembler/log_level_api/timestamp_stabilizer/
```

Primary headers:

```text
TLogApiTimestampStabilizerId.hpp
TLogApiTimestampStabilizerStatus.hpp
TLogApiTimeBasisKind.hpp
TLogApiCalendarKind.hpp
TLogApiTimestampPrecisionKind.hpp
TLogApiTimestampInputKind.hpp
TLogApiTimestampFallbackMode.hpp
TLogApiTimestampOffsetMode.hpp
TLogApiTimestampValue.hpp
TLogApiTimestampDelta.hpp
TLogApiTimestampStabilizerConfig.hpp
TLogApiTimestampStabilizationIssue.hpp
TLogApiTimestampStabilizationInput.hpp
TLogApiStabilizedTimestamp.hpp
TLogApiTimestampStabilizationResult.hpp
TLogApiTimestampStabilizerView.hpp
TLogApiTimestampStabilizer.hpp
TLogApiDefaultTimestampProfile.hpp
TLogApiTimestampSurface.hpp
```

Core types:

```text
TLogApiTimestampStabilizerConfig
TLogApiTimestampValue
TLogApiStabilizedTimestamp
TLogApiTimestampStabilizer
```

---

## 3.6 W06 — API Facade Content-Only Input

Folder:

```text
include/assembler/log_level_api/api_facade/
```

Primary headers:

```text
TLogApiFacadeId.hpp
TLogApiFacadeStatus.hpp
TLogApiContentInputStatus.hpp
TLogApiContentOnlyInput.hpp
TLogApiFacadeIssue.hpp
TLogApiFacadeConfigRef.hpp
TLogApiFacadeAdmission.hpp
TLogApiFacadeAcceptedContent.hpp
TLogApiFacadeInputResult.hpp
TLogApiFacadeView.hpp
TLogApiFacade.hpp
TLogApiFacadeSurface.hpp
```

Core types:

```text
TLogApiContentOnlyInput
TLogApiFacadeConfigRef
TLogApiFacadeAcceptedContent
TLogApiFacade
```

---

## 3.7 W07 — Envelope Carrier

Folder:

```text
include/assembler/log_level_api/envelope/
```

Primary headers:

```text
TLogApiEnvelopeId.hpp
TLogApiEnvelopeStatus.hpp
TLogApiEnvelopeIssue.hpp
TLogApiEnvelopeHeader.hpp
TLogApiEnvelopeContentBlock.hpp
TLogApiEnvelopeMetadataBlock.hpp
TLogApiEnvelopeTimestampBlock.hpp
TLogApiEnvelopeValidationBlock.hpp
TLogApiEnvelope.hpp
TLogApiEnvelopeView.hpp
TLogApiEnvelopeResult.hpp
TLogApiEnvelopeCarrierReport.hpp
TLogApiEnvelopeSurface.hpp
```

Core types:

```text
TLogApiEnvelope
TLogApiEnvelopeHeader
TLogApiEnvelopeView
```

---

## 3.8 W08 — Envelope Assembler Families

Folder:

```text
include/assembler/log_level_api/envelope_assembler/
```

Primary headers:

```text
TLogApiEnvelopeAssemblerId.hpp
TLogApiEnvelopeAssemblerStatus.hpp
TLogApiEnvelopeAssemblyIssue.hpp
TLogApiEnvelopeAssemblyProfile.hpp
TLogApiEnvelopeAssemblyInput.hpp
TLogApiEnvelopeAssemblyResult.hpp
TPlainLogApiEnvelopeAssembler.hpp
TValidatorComposedLogApiEnvelopeAssembler.hpp
TLogApiEnvelopeAssemblerView.hpp
TLogApiEnvelopeAssemblerFamilyReport.hpp
TLogApiEnvelopeAssemblerSurface.hpp
```

Core types:

```text
TPlainLogApiEnvelopeAssembler
TValidatorComposedLogApiEnvelopeAssembler
TLogApiEnvelopeAssemblyInput
```

---

## 3.9 W09 — Communication Bindings To Circulation

Folder:

```text
include/assembler/log_level_api/communication_bindings/
```

Primary headers:

```text
TLogApiEnvelopeProviderPluginAdapterDescriptor.hpp
TLogApiCirculationPortAdapterDescriptor.hpp
TLogApiCommunicationBindingDescriptor.hpp
TLogApiCommunicationBinding.hpp
TLogApiCommunicationBindingSurface.hpp
```

Core types:

```text
TLogApiEnvelopeProviderPluginAdapterDescriptor
TLogApiCirculationPortAdapterDescriptor
TLogApiCommunicationBinding
```

---

## 3.10 W10 — Default JSON Content Schemas

Folder:

```text
include/assembler/log_level_api/content/json_schemas/
```

Primary headers:

```text
TLogApiLogLevelKind.hpp
TLogApiJsonFieldValueKind.hpp
TLogApiJsonFieldPresenceKind.hpp
TLogApiJsonUnknownFieldPolicy.hpp
TLogApiJsonSchemaId.hpp
TLogApiJsonFieldId.hpp
TLogApiJsonDefaultValue.hpp
TLogApiJsonFieldDescriptor.hpp
TLogApiJsonFieldSet.hpp
TLogApiJsonLevelSchemaDescriptor.hpp
TLogApiJsonSchemaPackId.hpp
TLogApiDefaultJsonSchemaPack.hpp
TLogApiDefaultJsonSchemaFactory.hpp
TLogApiJsonSchemaPackView.hpp
TLogApiJsonLevelSchemaView.hpp
TLogApiJsonSchemaValidationInputDescriptor.hpp
TLogApiJsonSchemaIssue.hpp
TLogApiJsonSchemaRegistrationReport.hpp
TLogApiJsonSchemaSurface.hpp
```

Core types:

```text
TLogApiDefaultJsonSchemaPack
TLogApiJsonLevelSchemaDescriptor
TLogApiDefaultJsonSchemaFactory
```

---

## 3.11 W11 — Default C-Style Struct Primitive Schemas

Folder:

```text
include/assembler/log_level_api/content/c_style_struct_primitives/
```

Primary headers include:

```text
TLogApiCStructLogLevelKind.hpp
TLogApiCStructEndianKind.hpp
TLogApiCStructPrimitiveKind.hpp
TLogApiCStructFieldPresenceKind.hpp
TLogApiCStructFieldLayout.hpp
TLogApiCStructLevelSchemaDescriptor.hpp
TLogApiDefaultCStructSchemaFactory.hpp
TLogApiCStructPrimitiveSchemaSurface.hpp
```

Core types:

```text
TLogApiCStructFieldLayout
TLogApiCStructLayoutDescriptor
TLogApiDefaultCStructSchemaPack
```

---

## 3.12 W12 — Extended Tick Content Schema

Folder:

```text
include/assembler/log_level_api/content/mt5_extended_schemas/
```

Primary headers include:

```text
TLogApiMt5StructureKind.hpp
TLogApiMt5FieldDescriptor.hpp
TLogApiMt5StructureSchemaDescriptor.hpp
TLogApiMt5SchemaFactory.hpp
TLogApiMt5ExtendedSchemaSurface.hpp
```

Core types:

```text
TLogApiMt5StructureSchemaDescriptor
TLogApiMt5SchemaPack
TLogApiMt5SchemaFactory
```

---

## 3.13 W13 — Content Parser Core And Binding Surface

Folder:

```text
include/assembler/log_level_api/content_parser/
```

Primary headers include:

```text
TLogApiContentParserId.hpp
TLogApiContentParserKind.hpp
TLogApiContentParserProfile.hpp
TLogApiContentParserBindingDescriptor.hpp
TLogApiContentParseRequest.hpp
TLogApiContentParseResult.hpp
TLogApiOpaqueContentParser.hpp
TLogApiContentParserSurface.hpp
```

Core types:

```text
TLogApiContentParserProfile
TLogApiContentParserBindingDescriptor
TLogApiParsedContentRef
TLogApiOpaqueContentParser
```

---

## 3.14 W14–W18 — Dedicated Element Parsers

Folders:

```text
content_parser/json_level_parsers/
content_parser/c_style_struct_primitive_level_parsers/
content_parser/mt5_market_data_parsers/
content_parser/mt5_trade_structure_parsers/
content_parser/mt5_calendar_utility_parsers/
```

Core parser families:

```text
JSON level parsers
C-style struct primitive level parsers
MT5 market data parsers
MT5 trade structure parsers
MT5 calendar/utility parsers
```

Each parser family preserves:

```text
dedicated parser type
configuration-time selection
no hot-path dispatch
```

---

## 3.15 W19–W20 — Metadata Production Hardening

Folders:

```text
metadata_injector/profile_registry/
metadata_injector/default_field_packs/
```

Core types:

```text
TLogApiMetadataProfileRegistry
TLogApiMetadataProfileUpdater
TLogApiMetadataDefaultFieldPack
TLogApiMetadataFieldPackComposer
```

---

## 3.16 W21–W22 — Timestamp Production Hardening

Folders:

```text
timestamp_stabilizer/clock_calibration/
timestamp_stabilizer/optional_policies/
```

Core types:

```text
TLogApiClockSourceDescriptor
TLogApiClockSample
TLogApiClockCalibrator
TLogApiTimestampStabilizationRuleDescriptor
TLogApiTimestampProfileSwitchPlanner
```

---

## 3.17 W23–W24 — Final Envelope Shape And Exposure

Folders:

```text
envelope/final_shape/
envelope/readiness_exposure/
```

Core types:

```text
TLogApiFinalEnvelope
TLogApiEnvelopeValidationResultSlot
TLogApiEnvelopeReadinessView
TLogApiEnvelopeExposureView
TLogApiEnvelopeReadinessGate
```

---

## 3.18 W25–W26 — Circulation Integration Readiness

Folders:

```text
communication_bindings/circulation_handoff/
communication_bindings/circulation_integration/
```

Core types:

```text
TLogApiCirculationHandoffContract
TLogApiCirculationHandoffRequest
TLogApiCirculationAdmissionToken
TLogApiCirculationIntegrationSmokeSkeleton
```

---

## 3.19 W27 — Public API Surface

Folder:

```text
public_api/
```

Core types:

```text
TLogApiPublicCallRequest
TLogApiPublicCallResult
TLogApiPublicResolvedContext
TLogApiPublicApiFacade
TLogApiPublicApiUsageModel
```

---

## 3.20 W28–W30 — Production Hardening

Folders:

```text
diagnostics/
test_compliance/
production_readiness/
```

Core types:

```text
TLogApiDiagnosticRecord
TLogApiDiagnosticReport
TLogApiComplianceSuiteReport
TLogApiProductionReadinessGate
```

---

## 3.21 W31–W34 — Content Container / Batch Parsing

Folders:

```text
content_container/
content_container/mt5_market_data_container_parsers/
content_container/mt5_trade_structure_container_parsers/
content_container/mt5_calendar_utility_container_parsers/
```

Core types:

```text
TLogApiContentContainerRef
TLogApiContentContainerShape
TLogApiParsedContentBatchRef
TLogApiBatchEnvelopeStrategyDescriptor
MT5 array container parsers
```

---

## 4. Catalog Observations

### 4.1 Stable Themes

The type catalog shows these stable themes:

```text
Id / Status / View / Result
Descriptor / Profile / Registry
Issue / Report / Gate
InputRef / ParsedRef / BatchRef
```

### 4.2 Areas Likely To Need Cleanup

Potential cleanup targets:

```text
duplicate status enums
view naming normalization
result/issue naming consistency
parser profile id uniqueness
default pack composition conventions
validation result semantics
```

These should be tracked in the gap matrix.

---

## 5. Acceptance Criteria

This type/header catalog is accepted if it:

1. maps W01–W34 to component folders,
2. lists major headers per wave,
3. identifies core types per wave,
4. preserves parser/container separation,
5. preserves envelope/final-shape separation,
6. preserves circulation handoff boundary,
7. supports later gap analysis.

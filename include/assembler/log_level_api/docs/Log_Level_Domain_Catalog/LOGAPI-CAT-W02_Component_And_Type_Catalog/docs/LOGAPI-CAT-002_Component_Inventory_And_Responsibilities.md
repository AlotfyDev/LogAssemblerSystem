# LOGAPI-CAT-002 — Component Inventory And Responsibilities

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-002-DOC-001 | Document Title | Component Inventory And Responsibilities |
| LOGAPI-CAT-002-DOC-002 | File Name | `LOGAPI-CAT-002_Component_Inventory_And_Responsibilities.md` |
| LOGAPI-CAT-002-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-002-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-002-DOC-005 | Scope Level | Component inventory, responsibility map, ownership boundaries |
| LOGAPI-CAT-002-DOC-006 | Status | Component Catalog Draft |
| LOGAPI-CAT-002-DOC-007 | Previous Documents | `LOGAPI-CAT-000`, `LOGAPI-CAT-001` |
| LOGAPI-CAT-002-DOC-008 | Next Document | `LOGAPI-CAT-003_Type_And_Header_Catalog.md` |
| LOGAPI-CAT-002-DOC-009 | Diagram Index | `LOGAPI-CAT-002_component_dependency_graph.mmd`, `LOGAPI-CAT-002_component_ownership_map.mmd` |

---

## 2. Purpose

This document provides a component-level inventory for the Log Level API domain.

For each component family, it records:

```text
purpose
owns
does not own
primary inputs
primary outputs
related implementation waves
boundary rules
```

The goal is to prevent component collapse and to make future cleanup, extension, and production hardening easier.

---

## 3. Component Inventory

## 3.1 `api_configurator/`

### Purpose

Defines the configuration-time surface that resolves the active profile before any content is consumed.

### Owns

```text
configuration id/status
schema path selection
assembler family selection
active profile
configuration patch/result/view
default editable configuration
```

### Does Not Own

```text
content schemas
concrete parsers
metadata values
timestamp clocks
envelope assembly
circulation behavior
policy assignment
```

### Related Waves

```text
LOGAPI-W01_Configuration_Surface_And_Default_Profile
```

### Boundary Rule

```text
Configure first.
Do not discover schema, parser, metadata, timestamp, or assembler decisions inside hot path.
```

---

## 3.2 `content/`

### Purpose

Defines content profiles and schema path abstractions.

### Owns

```text
content profile id/status
schema path descriptors
JSON schema path descriptor
C-style struct primitive schema path descriptor
content input reference
content profile registry view
```

### Does Not Own

```text
all possible content schemas
concrete schema parsing
metadata struct
timestamp stabilization
validators
envelope assembly
```

### Related Waves

```text
LOGAPI-W02_Content_Profile_And_Schema_Paths
LOGAPI-W10_Default_JSON_Content_Schemas
LOGAPI-W11_Default_CStyle_Struct_Primitive_Schemas
LOGAPI-W12_Extended_Tick_Content_Schema
```

### Boundary Rule

```text
Content schema is open.
Default schemas are add-ons.
Content payload is separate from metadata and stabilized timestamp.
```

---

## 3.3 `content/json_schemas/`

### Purpose

Provides default JSON content schema descriptors per log level.

### Owns

```text
JSON level schema descriptors
JSON field descriptors
required/default/optional field descriptors
unknown field policy
schema pack views
validator input descriptors
```

### Does Not Own

```text
JSON parser implementation
validator implementation
metadata fields
stabilized timestamp
public API behavior
```

### Related Waves

```text
LOGAPI-W10_Default_JSON_Content_Schemas
```

### Boundary Rule

```text
Default JSON schemas are bundled conveniences, not a closed content universe.
```

---

## 3.4 `content/c_style_struct_primitives/`

### Purpose

Provides default C-style struct primitive schema descriptors.

### Owns

```text
fixed-width primitive descriptors
field layout offsets/sizes/alignment
endianness descriptors
reserved fields
level-specific default struct schemas
cross-language layout notes
```

### Does Not Own

```text
compiler-implied struct layout
binary parser implementation
concrete validators
metadata
timestamp
```

### Related Waves

```text
LOGAPI-W11_Default_CStyle_Struct_Primitive_Schemas
```

### Boundary Rule

```text
C-style struct schemas must be layout-specified, not compiler-implied.
```

---

## 3.5 `content/mt5_extended_schemas/`

### Purpose

Provides MetaTrader 5 extended content schema descriptors.

### Owns

```text
MqlTick schema
MqlRates schema
MqlBookInfo schema
MqlTradeRequest schema
MqlTradeCheckResult schema
MqlTradeResult schema
MqlTradeTransaction schema
MqlDateTime schema
MqlParam schema
MqlCalendarCountry schema
MqlCalendarEvent schema
MqlCalendarValue schema
MT5 validation input descriptors
```

### Does Not Own

```text
MQL5 runtime binding
binary ABI parsing
MT5 validators
metadata
timestamp
```

### Related Waves

```text
LOGAPI-W12_Extended_Tick_Content_Schema
```

### Boundary Rule

```text
MT5 schemas are add-on descriptors and do not imply direct MQL5 runtime binding.
```

---

## 3.6 `content_parser/`

### Purpose

Defines parser core, parser binding, parse request/result, parsed content references, and `OpaqueNoParse`.

### Owns

```text
content parser id/status/kind
parser input/output kinds
parser binding descriptors
parse request/result
parsed content ref/view
opaque/no-parse parser
default parser registry view
```

### Does Not Own

```text
all concrete parsers
metadata
timestamp
envelope assembly
validator semantics
```

### Related Waves

```text
LOGAPI-W13_Content_Parser_Core_And_Binding_Surface
```

### Boundary Rule

```text
Parser binding is configuration-time.
Parser execution is hot-path.
Parser discovery is never hot-path.
```

---

## 3.7 `content_parser/json_level_parsers/`

### Purpose

Provides dedicated parsers for default JSON log level schemas.

### Owns

```text
Trace JSON parser
Debug JSON parser
Info JSON parser
Notice JSON parser
Warning JSON parser
Error JSON parser
Critical JSON parser
Fatal JSON parser
JSON parsed field/content/result
JSON level parser profiles
```

### Does Not Own

```text
validators
metadata
timestamp
envelope assembly
generic runtime dispatch
```

### Related Waves

```text
LOGAPI-W14_Default_JSON_Level_Parsers
```

### Boundary Rule

```text
Each log level has a dedicated parser type.
No generic hot-path parser dispatch.
```

---

## 3.8 `content_parser/c_style_struct_primitive_level_parsers/`

### Purpose

Provides dedicated parsers for default C-style struct primitive log level schemas.

### Owns

```text
Trace C-struct parser
Debug C-struct parser
Info C-struct parser
Notice C-struct parser
Warning C-struct parser
Error C-struct parser
Critical C-struct parser
Fatal C-struct parser
offset-based field parsing
parsed C-struct field/content/result
```

### Does Not Own

```text
compiler struct layout
metadata
timestamp
validators
generic runtime dispatch
```

### Related Waves

```text
LOGAPI-W15_Default_CStyle_Struct_Primitive_Level_Parsers
```

### Boundary Rule

```text
Read offsets and sizes from schema descriptors.
Do not infer layout from compiler packing.
```

---

## 3.9 `content_parser/mt5_market_data_parsers/`

### Purpose

Provides dedicated element parsers for MT5 market data structures.

### Owns

```text
MqlTick parser
MqlRates parser
MqlBookInfo parser
market-data parsed fields/content/results
MT5 market parser profiles
```

### Does Not Own

```text
container loops
MQL5 runtime binding
binary ABI parsing
validators
metadata/timestamp/envelope
```

### Related Waves

```text
LOGAPI-W16_MT5_Market_Data_Parsers
```

---

## 3.10 `content_parser/mt5_trade_structure_parsers/`

### Purpose

Provides dedicated element parsers for MT5 trade structures.

### Owns

```text
MqlTradeRequest parser
MqlTradeCheckResult parser
MqlTradeResult parser
MqlTradeTransaction parser
trade parsed fields/content/results
```

### Does Not Own

```text
container loops
trade validators
MQL5 runtime binding
policy behavior
```

### Related Waves

```text
LOGAPI-W17_MT5_Trade_Structure_Parsers
```

---

## 3.11 `content_parser/mt5_calendar_utility_parsers/`

### Purpose

Provides dedicated element parsers for MT5 utility and calendar structures.

### Owns

```text
MqlDateTime parser
MqlParam parser
MqlCalendarCountry parser
MqlCalendarEvent parser
MqlCalendarValue parser
```

### Does Not Own

```text
calendar semantic normalization
calendar value scaling policy
MQL5 runtime binding
validators
```

### Related Waves

```text
LOGAPI-W18_MT5_Calendar_And_Utility_Parsers
```

---

## 3.12 `content_container/`

### Purpose

Defines container/batch parsing abstractions.

### Owns

```text
content container id/kind/shape/ref
container parser profile
container parse request/result
parsed content batch ref/view
batch envelope strategy descriptor
container readiness
```

### Does Not Own

```text
MT5-specific loops
JSON batch parsers
C-style batch parsers
envelope stream implementation
circulation handoff
```

### Related Waves

```text
LOGAPI-W31_Content_Container_Core_And_Batch_Parse_Model
```

### Boundary Rule

```text
Container parser owns the loop.
Element parser owns parsing one element.
No runtime dispatch inside the loop.
```

---

## 3.13 `content_container/mt5_market_data_container_parsers/`

### Purpose

Provides dedicated parsers for MT5 market data arrays.

### Owns

```text
MqlTick[] container parser
MqlRates[] container parser
MqlBookInfo[] container parser
```

### Does Not Own

```text
element parser internals
validators
envelope batch materialization
circulation
```

### Related Waves

```text
LOGAPI-W32_MT5_Market_Data_Container_Parsers
```

---

## 3.14 `content_container/mt5_trade_structure_container_parsers/`

### Purpose

Provides dedicated parsers for MT5 trade structure arrays.

### Owns

```text
MqlTradeRequest[] container parser
MqlTradeCheckResult[] container parser
MqlTradeResult[] container parser
MqlTradeTransaction[] container parser
```

### Does Not Own

```text
trade validation
trade execution
broker integration
```

### Related Waves

```text
LOGAPI-W33_MT5_Trade_Structure_Container_Parsers
```

---

## 3.15 `content_container/mt5_calendar_utility_container_parsers/`

### Purpose

Provides dedicated parsers for MT5 calendar and utility arrays.

### Owns

```text
MqlDateTime[] container parser
MqlParam[] container parser
MqlCalendarCountry[] container parser
MqlCalendarEvent[] container parser
MqlCalendarValue[] container parser
```

### Does Not Own

```text
calendar semantic interpretation
macroeconomic analysis
value scaling policy
```

### Related Waves

```text
LOGAPI-W34_MT5_Calendar_And_Utility_Container_Parsers
```

---

## 3.16 `validator/`

### Purpose

Defines validator contracts and validation result carriers.

### Owns

```text
validator id/status
validation mode/severity
validator capability and safe-point kinds
validation issue/result
validator binding descriptors
validation request carrier
```

### Does Not Own

```text
concrete validators
payload accept/reject action
policy behavior
metadata/timestamp/envelope assembly
```

### Related Waves

```text
LOGAPI-W03_Validator_Contract_And_Binding_Surface
```

### Boundary Rule

```text
Validation result is evidence.
Accept/reject action is user/policy decision, not validator ownership.
```

---

## 3.17 `metadata_injector/`

### Purpose

Defines metadata structures, field values, update sets, prepared metadata blocks, profile registry, and default field packs.

### Owns

```text
metadata struct descriptors
metadata fields and values
metadata update sets
prepared metadata block
metadata profile registry
default metadata field packs
```

### Does Not Own

```text
content schemas
timestamp
policy assignment
persistence
security
```

### Related Waves

```text
LOGAPI-W04_Metadata_Struct_And_Field_Values
LOGAPI-W19_Metadata_Profile_Registry_And_Update_Model
LOGAPI-W20_Metadata_Default_Field_Packs
```

### Boundary Rule

```text
Metadata is configuration/update concern, not policy by default.
```

---

## 3.18 `timestamp_stabilizer/`

### Purpose

Defines timestamp stabilizer configuration, timestamp values, stabilized timestamp, clock calibration, and optional policy-sensitive timestamp descriptors.

### Owns

```text
timestamp stabilizer config
timestamp source/input/fallback/offset modes
timestamp value/delta/stabilized timestamp
clock source descriptors
clock samples
offset/drift/skew reports
optional timestamp policy-sensitive descriptors
```

### Does Not Own

```text
content payload
metadata
OS clock acquisition
full policy assignment
calendar conversion implementation
```

### Related Waves

```text
LOGAPI-W05_Timestamp_Stabilizer_Config_And_Model
LOGAPI-W21_Timestamp_Clock_Source_And_Calibration
LOGAPI-W22_Timestamp_Stabilization_Policies_Optional
```

---

## 3.19 `api_facade/`

### Purpose

Defines internal consuming facade content-only admission.

### Owns

```text
content-only input
facade config refs
facade admission
accepted content
facade input result/view
```

### Does Not Own

```text
public API overloads
full envelope assembly
schema selection
per-call config
```

### Related Waves

```text
LOGAPI-W06_Api_Facade_Content_Only_Input
```

---

## 3.20 `public_api/`

### Purpose

Defines stable public API call surfaces and usage model.

### Owns

```text
public call id/status
public input kind
opaque/json/cstruct payload refs
resolved public context
public call request/result/view
public usage model
```

### Does Not Own

```text
full production execution flow
specialized parser orchestration
envelope assembly
real circulation integration
```

### Related Waves

```text
LOGAPI-W27_Public_API_Surface_And_Usage_Model
```

---

## 3.21 `envelope/`

### Purpose

Defines envelope carrier, final envelope shape, slots, validation result slot, readiness and exposure views.

### Owns

```text
envelope id/version/status
header
content slot
metadata slot
timestamp slot
validation result slot
readiness view
exposure view
```

### Does Not Own

```text
assembly policy
payload accept/reject action
circulation handoff execution
persistence
```

### Related Waves

```text
LOGAPI-W07_Envelope_Carrier
LOGAPI-W23_Envelope_Final_Shape_And_Identity
LOGAPI-W24_Envelope_Readiness_And_Exposure_View
```

---

## 3.22 `envelope_assembler/`

### Purpose

Defines envelope assembler families.

### Owns

```text
plain envelope assembler
validator-composed envelope assembler
assembly input/result/profile
```

### Does Not Own

```text
schema parsing
metadata generation
timestamp acquisition
circulation handoff
policy decision
```

### Related Waves

```text
LOGAPI-W08_Envelope_Assembler_Families
```

---

## 3.23 `communication_bindings/`

### Purpose

Defines LogAPI-to-Circulation binding and handoff readiness surfaces.

### Owns

```text
provider plugin adapter descriptor
circulation port adapter descriptor
handoff contract
handoff token
integration smoke skeleton
```

### Does Not Own

```text
circulation engine
placement
queues
waiting lists
round managers
dispatcher
bridge orchestration
```

### Related Waves

```text
LOGAPI-W09_Communication_Bindings_To_Circulation
LOGAPI-W25_Circulation_Handoff_Contract
LOGAPI-W26_Circulation_Integration_Smoke_Skeleton
```

---

## 3.24 `diagnostics/`

### Purpose

Defines diagnostic and failure classification for Log Level API.

### Owns

```text
diagnostic records
failure kinds
failure boundary kinds
diagnostic reports
diagnostic gates
diagnostic summaries
```

### Does Not Own

```text
logging backend
telemetry exporter
persistence
recovery engine
```

### Related Waves

```text
LOGAPI-W28_Diagnostics_And_Failure_Model
```

---

## 3.25 `test_compliance/`

### Purpose

Defines compliance assertions, test cases, negative catalog, and compliance gate.

### Owns

```text
compliance dimensions
assertions
test case descriptors
negative catalog
suite report
compliance gate
```

### Does Not Own

```text
CI runner
external test framework
deployment readiness
```

### Related Waves

```text
LOGAPI-W29_Test_Compliance_Suite
```

---

## 3.26 `production_readiness/`

### Purpose

Defines production readiness criteria, evidence references, report, summary, and readiness gate.

### Owns

```text
readiness criteria
evidence refs
readiness issues
readiness report
readiness summary
readiness gate
```

### Does Not Own

```text
deployment
runtime monitoring
telemetry backend
persistence
security gate
```

### Related Waves

```text
LOGAPI-W30_Production_Readiness_Gate
```

---

## 4. Ownership Summary

The domain is organized around six major ownership clusters:

```text
Configuration and public entry
Content/schema/parser/container
Preparation components
Envelope shape and readiness
Circulation boundary contracts
Hardening and readiness
```

The component ownership map is represented in:

```text
diagrams/LOGAPI-CAT-002_component_ownership_map.mmd
```

---

## 5. Dependency Summary

High-level dependency direction:

```text
configuration
    → content profiles
    → schema/parser/container
    → metadata/timestamp
    → envelope
    → exposure
    → handoff contract
    → smoke integration
    → public API / diagnostics / compliance / readiness
```

The dependency graph is represented in:

```text
diagrams/LOGAPI-CAT-002_component_dependency_graph.mmd
```

---

## 6. Acceptance Criteria

This component inventory is accepted if it:

1. covers all implemented component families from W01–W34,
2. identifies what each component owns,
3. identifies what each component must not own,
4. preserves the circulation boundary,
5. preserves policy assignment deferral,
6. supports later type/header cataloging,
7. includes component ownership and dependency diagrams.

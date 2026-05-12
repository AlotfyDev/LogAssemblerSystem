# LOGAPI-CAT-004 — End-To-End Flow Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-004-DOC-001 | Document Title | End-To-End Flow Model |
| LOGAPI-CAT-004-DOC-002 | File Name | `LOGAPI-CAT-004_End_To_End_Flow_Model.md` |
| LOGAPI-CAT-004-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-004-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-004-DOC-005 | Scope Level | End-to-end flows, hot-path flow, configuration flow, handoff boundary |
| LOGAPI-CAT-004-DOC-006 | Status | Behavioral Catalog Draft |
| LOGAPI-CAT-004-DOC-007 | Previous Documents | `LOGAPI-CAT-000` through `LOGAPI-CAT-003` |
| LOGAPI-CAT-004-DOC-008 | Next Document | `LOGAPI-CAT-005_Behavioral_State_And_Readiness_Model.md` |
| LOGAPI-CAT-004-DOC-009 | Related Implementation Waves | `LOGAPI-W01` through `LOGAPI-W34` |
| LOGAPI-CAT-004-DOC-010 | Diagram Index | `LOGAPI-CAT-004_e2e_opaque_flow.mmd`, `LOGAPI-CAT-004_e2e_json_flow.mmd`, `LOGAPI-CAT-004_e2e_cstruct_flow.mmd`, `LOGAPI-CAT-004_e2e_mt5_single_flow.mmd`, `LOGAPI-CAT-004_e2e_mt5_batch_flow.mmd` |

---

## 2. Purpose

This document defines the end-to-end behavioral flows of the Log Level API domain.

It answers:

```text
How does content move from a configured public input path,
through parsing and preparation,
into an envelope,
then into readiness/exposure,
then toward the circulation handoff boundary?
```

This document is about Log Level API behavior only.

It does not describe Circulation internals.

---

## 3. Canonical Phases

Every Log Level API flow has two major phases.

### 3.1 Configuration Phase

The configuration phase resolves:

```text
active profile
content schema/profile
parser binding
metadata profile
timestamp profile
assembler family
circulation handoff target descriptor
optional timestamp policy-sensitive descriptors
```

Configuration happens before the hot path.

### 3.2 Hot Path / Consuming Phase

The hot path consumes content only.

The hot path may execute:

```text
content-only public API admission
dedicated parser
metadata preparation
timestamp stabilization
envelope assembly
final envelope shaping
exposure/readiness view
handoff contract
```

The hot path does not discover parsers or schemas.

---

## 4. Flow 1 — Opaque Payload Path

The opaque path is used when no parsing is required.

### 4.1 Configuration

```text
active profile = opaque.pass_through
parser binding = OpaqueNoParse
metadata profile = resolved
timestamp profile = resolved
assembler family = resolved
handoff target = resolved
```

### 4.2 Hot Path

```text
OpaquePayloadRef
→ Public API content-only call
→ OpaqueNoParse parser
→ parsed content ref = opaque
→ metadata block
→ stabilized timestamp
→ envelope assembly/final shape
→ exposure view
→ handoff contract
```

### 4.3 Notes

The opaque path proves that parsing is not required merely to transport content.

The content remains opaque, but still receives metadata and stabilized timestamp in the envelope.

---

## 5. Flow 2 — JSON Input Path

The JSON path uses default JSON schemas and dedicated level parsers.

### 5.1 Configuration

```text
JSON schema profile selected
level-specific parser selected
metadata profile resolved
timestamp profile resolved
assembler family resolved
```

### 5.2 Hot Path

```text
JsonTextRef
→ Public API content-only call
→ dedicated JSON level parser
→ parsed JSON field view
→ metadata block
→ stabilized timestamp
→ envelope
→ exposure
→ handoff contract
```

### 5.3 Notes

Default JSON schemas are minimal:

```text
required: message
defaulted: level
optional: code, context, payload_timestamp
```

Metadata is not inside JSON schema.

Stabilized timestamp is not inside JSON schema.

---

## 6. Flow 3 — C-Style Struct Primitive Path

The C-style struct primitive path uses explicit layout descriptors.

### 6.1 Configuration

```text
C-style struct primitive schema selected
level-specific C-struct parser selected
fixed offsets/sizes/endian known
metadata profile resolved
timestamp profile resolved
```

### 6.2 Hot Path

```text
CStructPayloadRef
→ Public API content-only call
→ dedicated C-struct level parser
→ parsed field view
→ metadata block
→ stabilized timestamp
→ envelope
→ exposure
→ handoff contract
```

### 6.3 Notes

C-style schemas are layout-specified, not compiler-implied.

The parser reads declared offsets and sizes.

---

## 7. Flow 4 — MT5 Single Structure Path

The MT5 single structure path uses a dedicated parser per MT5 structure.

### 7.1 Supported Structure Groups

```text
market data:
    MqlTick
    MqlRates
    MqlBookInfo

trade:
    MqlTradeRequest
    MqlTradeCheckResult
    MqlTradeResult
    MqlTradeTransaction

calendar / utility:
    MqlDateTime
    MqlParam
    MqlCalendarCountry
    MqlCalendarEvent
    MqlCalendarValue
```

### 7.2 Configuration

```text
MT5 structure schema selected
dedicated MT5 structure parser selected
metadata profile resolved
timestamp profile resolved
assembler family resolved
```

### 7.3 Hot Path

```text
MT5 input view
→ dedicated MT5 structure parser
→ parsed MT5 structure view
→ metadata block
→ stabilized timestamp
→ envelope
→ exposure
→ handoff contract
```

### 7.4 Notes

Current MT5 parsers use explicit C++ input views.

They do not bind directly to the MQL5 runtime.

They do not parse binary ABI layout.

---

## 8. Flow 5 — MT5 Batch / Container Path

The MT5 batch path supports arrays/containers.

### 8.1 Supported Groups

```text
market data containers:
    MqlTick[]
    MqlRates[]
    MqlBookInfo[]

trade containers:
    MqlTradeRequest[]
    MqlTradeCheckResult[]
    MqlTradeResult[]
    MqlTradeTransaction[]

calendar / utility containers:
    MqlDateTime[]
    MqlParam[]
    MqlCalendarCountry[]
    MqlCalendarEvent[]
    MqlCalendarValue[]
```

### 8.2 Configuration

```text
container shape selected
container parser profile selected
element parser fixed
batch envelope strategy selected
metadata profile resolved
timestamp profile resolved
```

### 8.3 Hot Path

```text
content container ref
→ dedicated container parser
→ fixed loop over known element type
→ dedicated element parser
→ parsed batch ref
→ batch envelope strategy
→ envelope/exposure/handoff later
```

### 8.4 Notes

Container parser owns the loop.

Element parser owns parsing one element.

There is no runtime dispatch inside the loop.

---

## 9. Validation Flow

Validation result is a slot in the final envelope, but validation action is not the validator’s responsibility.

```text
validator result = valid / invalid / not evaluated
```

Payload acceptance or rejection based on validation result is:

```text
user configuration or future policy concern
```

The validator does not own the action.

---

## 10. Circulation Boundary Flow

The Log Level API produces:

```text
ready final envelope exposure
```

Then the handoff contract produces:

```text
contract-level admission token
```

The Log Level API does not own:

```text
circulation placement
slots
queues
waiting lists
round managers
dispatcher
```

---

## 11. Known Flow Gaps

The following are not yet fully implemented as one production public API call:

```text
public JSON call → JSON parser → metadata/timestamp → envelope → handoff
public C-struct call → parser → metadata/timestamp → envelope → handoff
public MT5 typed call → parser → metadata/timestamp → envelope → handoff
batch container → envelope strategy → actual envelope production
```

The components exist, but the final all-in-one production public API orchestration remains a logical extension.

---

## 12. Acceptance Criteria

This flow model is accepted if it:

1. covers opaque, JSON, C-style struct, MT5 single, and MT5 batch paths,
2. separates configuration phase from hot path,
3. preserves content-only public API,
4. records parser binding as configuration-time,
5. keeps metadata and timestamp separate from content,
6. treats validation result as evidence only,
7. stops at the Circulation handoff boundary.

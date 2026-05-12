# LOGAPI-CAT-006 — Content Schema And Parser Catalog

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-006-DOC-001 | Document Title | Content Schema And Parser Catalog |
| LOGAPI-CAT-006-DOC-002 | File Name | `LOGAPI-CAT-006_Content_Schema_And_Parser_Catalog.md` |
| LOGAPI-CAT-006-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-006-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-006-DOC-005 | Scope Level | Content schema families, parser families, parser binding doctrine, schema/parser separation |
| LOGAPI-CAT-006-DOC-006 | Status | Schema/Parser Catalog Draft |
| LOGAPI-CAT-006-DOC-007 | Related Implementation Waves | `LOGAPI-W02`, `W10` through `W18`, `W31` through `W34` |
| LOGAPI-CAT-006-DOC-008 | Diagram Index | `LOGAPI-CAT-006_schema_parser_binding.mmd`, `LOGAPI-CAT-006_parser_family_map.mmd` |

---

## 2. Purpose

This document catalogs the schema and parser model inside the Log Level API domain.

It answers:

```text
What schemas exist,
what parser families exist,
how are schemas and parsers bound,
and why does parser selection happen at configuration time rather than inside the hot path?
```

---

## 3. Core Doctrine

The content layer follows this rule:

```text
schema = contract
parser = reader of that contract
validator = optional constraint checker
```

A schema describes what content shape exists.

A parser reads that content shape.

A validator, if present later, verifies constraints above parsing.

---

## 4. Content Schema Families

## 4.1 Content Profile / Schema Path Layer

Implemented by:

```text
LOGAPI-W02_Content_Profile_And_Schema_Paths
```

Purpose:

```text
Provide open content profile descriptors and select schema paths.
```

Schema paths currently include:

```text
JSON
C-style struct primitives
```

MT5 schemas are add-ons, not core closed content.

---

## 4.2 Default JSON Schemas

Implemented by:

```text
LOGAPI-W10_Default_JSON_Content_Schemas
```

The default JSON schemas are level-specific:

```text
Trace
Debug
Info
Notice
Warning
Error
Critical
Fatal
```

Default payload structure:

```text
required:
    message

defaulted:
    level

optional:
    code
    context
    payload_timestamp
```

Boundary:

```text
metadata is not part of JSON content schema
stabilized timestamp is not part of JSON content schema
```

---

## 4.3 Default C-Style Struct Primitive Schemas

Implemented by:

```text
LOGAPI-W11_Default_CStyle_Struct_Primitive_Schemas
```

The default C-style struct primitive schemas are level-specific and layout-defined.

Default minimal layout:

```text
offset  size  field
0       2     schema_marker       required UInt16
2       1     level_code          defaulted UInt8
3       1     flags               optional UInt8
4       4     message_id          required UInt32
8       8     numeric_code        optional Int64
16      8     payload_timestamp   optional Int64, source-provided only
24      104   reserved            reserved bytes
```

Boundary:

```text
layout is explicit
not compiler-implied
metadata is not inside struct
stabilized timestamp is not inside struct
```

---

## 4.4 MT5 Extended Schemas

Implemented by:

```text
LOGAPI-W12_Extended_Tick_Content_Schema
```

The MT5 schema pack covers:

```text
MqlDateTime
MqlParam
MqlRates
MqlBookInfo
MqlTradeRequest
MqlTradeCheckResult
MqlTradeResult
MqlTradeTransaction
MqlTick
MqlCalendarCountry
MqlCalendarEvent
MqlCalendarValue
```

Boundary:

```text
schemas describe MT5 structures
schemas do not bind to MQL5 runtime
schemas do not imply binary ABI parsing
```

---

## 5. Parser Core

Implemented by:

```text
LOGAPI-W13_Content_Parser_Core_And_Binding_Surface
```

Parser core defines:

```text
parser id
parser status
parser kind
parser input kind
parsed content kind
parser capabilities
parser profile
parser binding descriptor
parse request/result
parsed content ref/view
OpaqueNoParse
```

The central rule:

```text
Parser binding is configuration-time.
Parser execution is hot-path.
Parser discovery is never hot-path.
```

---

## 6. Parser Families

## 6.1 Opaque / NoParse

Implemented in W13.

Purpose:

```text
Transport content without parsing it.
```

Used when:

```text
the caller wants opaque payload carriage
the Log Level API does not need field views
the content will be interpreted later by another boundary
```

---

## 6.2 Default JSON Level Parsers

Implemented by:

```text
LOGAPI-W14_Default_JSON_Level_Parsers
```

Dedicated parser types:

```text
TTraceJsonContentParser
TDebugJsonContentParser
TInfoJsonContentParser
TNoticeJsonContentParser
TWarningJsonContentParser
TErrorJsonContentParser
TCriticalJsonContentParser
TFatalJsonContentParser
```

Rule:

```text
One parser type per default JSON level schema.
No generic JSON-level parser dispatch in hot path.
```

---

## 6.3 Default C-Style Struct Primitive Level Parsers

Implemented by:

```text
LOGAPI-W15_Default_CStyle_Struct_Primitive_Level_Parsers
```

Dedicated parser types:

```text
TTraceCStructPrimitiveParser
TDebugCStructPrimitiveParser
TInfoCStructPrimitiveParser
TNoticeCStructPrimitiveParser
TWarningCStructPrimitiveParser
TErrorCStructPrimitiveParser
TCriticalCStructPrimitiveParser
TFatalCStructPrimitiveParser
```

Rule:

```text
Read explicit offsets/sizes from the schema.
Do not use compiler struct layout.
```

---

## 6.4 MT5 Structure Parsers

Implemented by:

```text
LOGAPI-W16_MT5_Market_Data_Parsers
LOGAPI-W17_MT5_Trade_Structure_Parsers
LOGAPI-W18_MT5_Calendar_And_Utility_Parsers
```

Parser families:

```text
market data:
    TMqlTickContentParser
    TMqlRatesContentParser
    TMqlBookInfoContentParser

trade:
    TMqlTradeRequestContentParser
    TMqlTradeCheckResultContentParser
    TMqlTradeResultContentParser
    TMqlTradeTransactionContentParser

calendar / utility:
    TMqlDateTimeContentParser
    TMqlParamContentParser
    TMqlCalendarCountryContentParser
    TMqlCalendarEventContentParser
    TMqlCalendarValueContentParser
```

Rule:

```text
One parser per MT5 structure.
No generic MT5 parser dispatch in the hot path.
```

---

## 7. Content Container / Batch Parser Model

Implemented by:

```text
LOGAPI-W31_Content_Container_Core_And_Batch_Parse_Model
LOGAPI-W32_MT5_Market_Data_Container_Parsers
LOGAPI-W33_MT5_Trade_Structure_Container_Parsers
LOGAPI-W34_MT5_Calendar_And_Utility_Container_Parsers
```

Core doctrine:

```text
Single parser parses one known structure.
Container parser parses one known container of that structure.
Container parser owns the loop.
Element parser owns parsing one element.
No runtime dispatch inside the loop.
```

Container parser families:

```text
MT5 market data arrays
MT5 trade structure arrays
MT5 calendar/utility arrays
```

---

## 8. Parser vs Validator

Parser failure means:

```text
the content could not be read into the expected parsed view
```

Validator failure means:

```text
the content was parsed but violates additional constraints
```

Currently, concrete validators are not mandatory in the hot path.

Validation is optional and remains a separate concern.

---

## 9. Schema / Parser / Binding Flow

The canonical relation:

```text
schema descriptor
    ↓
parser profile
    ↓
parser binding
    ↓
content input
    ↓
parsed content ref/view
```

This relation is visualized in:

```text
diagrams/LOGAPI-CAT-006_schema_parser_binding.mmd
```

---

## 10. Current Parser Coverage

| Family | Schema Wave | Parser Wave | Container Wave |
|---|---:|---:|---:|
| Opaque | N/A | W13 | N/A |
| JSON levels | W10 | W14 | Deferred |
| C-style struct primitive levels | W11 | W15 | Deferred |
| MT5 market data | W12 | W16 | W32 |
| MT5 trade structures | W12 | W17 | W33 |
| MT5 calendar/utility | W12 | W18 | W34 |

---

## 11. Known Parser Gaps

Known gaps include:

```text
JSON array/batch parsers
C-style struct primitive array parsers
production JSON parser replacement for minimal extractor
binary ABI parser for MT5 direct memory
parser output compact field table
partial-success batch parse policy
parser benchmark suite
```

These belong in the gap matrix, not in this catalog document.

---

## 12. Acceptance Criteria

This schema/parser catalog is accepted if it:

1. distinguishes schema, parser, and validator,
2. covers JSON, C-style struct, MT5, opaque, and batch/container paths,
3. preserves configuration-time parser binding,
4. prohibits hot-path parser discovery,
5. documents current parser coverage,
6. identifies known parser gaps without expanding scope.

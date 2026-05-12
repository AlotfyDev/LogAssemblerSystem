# LOGAPI-CAT-007 — MT5 Content And Container Catalog

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-007-DOC-001 | Document Title | MT5 Content And Container Catalog |
| LOGAPI-CAT-007-DOC-002 | File Name | `LOGAPI-CAT-007_MT5_Content_And_Container_Catalog.md` |
| LOGAPI-CAT-007-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-007-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-007-DOC-005 | Scope Level | MT5 schemas, MT5 dedicated parsers, MT5 containers, MT5 batch parsing |
| LOGAPI-CAT-007-DOC-006 | Status | MT5 Catalog Draft |
| LOGAPI-CAT-007-DOC-007 | Related Implementation Waves | `LOGAPI-W12`, `W16`, `W17`, `W18`, `W31`, `W32`, `W33`, `W34` |
| LOGAPI-CAT-007-DOC-008 | Diagram Index | `LOGAPI-CAT-007_mt5_structure_map.mmd`, `LOGAPI-CAT-007_mt5_container_loop_model.mmd` |

---

## 2. Purpose

This document catalogs the MT5-specific content schemas, parsers, and container parsers in Log Level API.

It answers:

```text
Which MT5 structures are covered,
which parsers read them,
which array/container parsers exist,
and what remains out of scope?
```

---

## 3. MT5 Schema Coverage

Implemented by:

```text
LOGAPI-W12_Extended_Tick_Content_Schema
```

Covered structures:

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

---

## 4. MT5 Structure Groups

## 4.1 Market Data

```text
MqlTick
MqlRates
MqlBookInfo
```

Purpose:

```text
fast current prices
historical rates
depth of market / market book
```

Element parser wave:

```text
LOGAPI-W16_MT5_Market_Data_Parsers
```

Container parser wave:

```text
LOGAPI-W32_MT5_Market_Data_Container_Parsers
```

---

## 4.2 Trade Structures

```text
MqlTradeRequest
MqlTradeCheckResult
MqlTradeResult
MqlTradeTransaction
```

Purpose:

```text
trade request description
trade request pre-check result
trade server response
trade transaction description
```

Element parser wave:

```text
LOGAPI-W17_MT5_Trade_Structure_Parsers
```

Container parser wave:

```text
LOGAPI-W33_MT5_Trade_Structure_Container_Parsers
```

---

## 4.3 Calendar And Utility

```text
MqlDateTime
MqlParam
MqlCalendarCountry
MqlCalendarEvent
MqlCalendarValue
```

Purpose:

```text
date/time decomposition
indicator parameter value carrier
economic calendar country
economic calendar event
economic calendar value
```

Element parser wave:

```text
LOGAPI-W18_MT5_Calendar_And_Utility_Parsers
```

Container parser wave:

```text
LOGAPI-W34_MT5_Calendar_And_Utility_Container_Parsers
```

---

## 5. MT5 Element Parser Catalog

## 5.1 Market Data Parsers

```text
TMqlTickContentParser
TMqlRatesContentParser
TMqlBookInfoContentParser
```

## 5.2 Trade Parsers

```text
TMqlTradeRequestContentParser
TMqlTradeCheckResultContentParser
TMqlTradeResultContentParser
TMqlTradeTransactionContentParser
```

## 5.3 Calendar / Utility Parsers

```text
TMqlDateTimeContentParser
TMqlParamContentParser
TMqlCalendarCountryContentParser
TMqlCalendarEventContentParser
TMqlCalendarValueContentParser
```

All are dedicated parser types.

None performs runtime dispatch.

---

## 6. MT5 Container Parser Catalog

## 6.1 Market Data Containers

```text
MqlTick[]       → TMqlTickArrayContainerParser
MqlRates[]      → TMqlRatesArrayContainerParser
MqlBookInfo[]   → TMqlBookInfoArrayContainerParser
```

## 6.2 Trade Containers

```text
MqlTradeRequest[]       → TMqlTradeRequestArrayContainerParser
MqlTradeCheckResult[]   → TMqlTradeCheckResultArrayContainerParser
MqlTradeResult[]        → TMqlTradeResultArrayContainerParser
MqlTradeTransaction[]   → TMqlTradeTransactionArrayContainerParser
```

## 6.3 Calendar / Utility Containers

```text
MqlDateTime[]          → TMqlDateTimeArrayContainerParser
MqlParam[]             → TMqlParamArrayContainerParser
MqlCalendarCountry[]   → TMqlCalendarCountryArrayContainerParser
MqlCalendarEvent[]     → TMqlCalendarEventArrayContainerParser
MqlCalendarValue[]     → TMqlCalendarValueArrayContainerParser
```

---

## 7. MT5 Batch Parsing Doctrine

For MT5 containers:

```text
Container parser owns the loop.
Element parser owns one element.
The container parser uses exactly one element parser.
No generic MT5 parser dispatch occurs inside the loop.
```

Example:

```text
MqlTick[]
    → TMqlTickArrayContainerParser
        → TMqlTickContentParser
```

Not allowed:

```text
void* mt5_array
    → GenericMt5Parser
        → switch(type)
```

---

## 8. Input View Model

The current MT5 parser implementation uses explicit C++ input views.

Examples:

```text
TLogApiMt5MqlTickInputView
TLogApiMt5MqlRatesInputView
TLogApiMt5MqlBookInfoInputView
TLogApiMt5MqlTradeRequestInputView
TLogApiMt5MqlCalendarValueInputView
```

These input views mirror MT5 documented fields but do not depend on MQL5 runtime binding.

---

## 9. MT5 Non-Ownership Rules

The MT5 catalog does not own:

```text
MQL5 runtime binding
direct terminal memory access
binary ABI layout
broker-specific trade semantics
calendar value scaling semantics
trade execution
macroeconomic interpretation
Binance mapping
```

Those are logical extensions or separate integration layers.

---

## 10. Batch Envelope Strategy

W31 defined two batch envelope strategy descriptors:

```text
BatchAsSingleEnvelope
ElementAsEnvelopeStream
```

MT5 container parsers currently produce parsed batch refs.

They do not yet implement envelope streaming or batch-as-single-envelope materialization.

That remains a future extension.

---

## 11. MT5 Diagram Index

This document is accompanied by:

```text
diagrams/LOGAPI-CAT-007_mt5_structure_map.mmd
diagrams/LOGAPI-CAT-007_mt5_container_loop_model.mmd
```

---

## 12. Known MT5 Gaps

Known MT5 gaps include:

```text
direct MQL5 runtime binding
binary layout mapping
partial success policy for arrays
Binance-compatible tick mapping
calendar value scale/sentinel helper semantics
generated bindings for C++ / MQL5 / C# / Python
benchmark suite for high-frequency tick arrays
```

---

## 13. Acceptance Criteria

This MT5 catalog is accepted if it:

1. lists all MT5 structures covered by W12,
2. maps each structure to its dedicated parser,
3. maps each array/container to its dedicated container parser,
4. preserves no-dispatch hot-path rule,
5. excludes MT5 runtime binding,
6. tracks MT5-specific gaps separately from Circulation domain concerns.

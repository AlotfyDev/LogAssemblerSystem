# Integrated Coverage Matrix — CME-W15

| Area | Covered By |
|---|---|
| IDs / States | W01 |
| Views / Reports / Diagnostics primitives | W02 |
| Capacity profiles | W03 |
| Slot / Container | W04 |
| Container Registry | W05 |
| BundleAgent / Moderator | W06 |
| WaitingLists / RoundManager | W07 |
| Reference Handles / Validity | W08 |
| ReferencePrecalculator | W09 |
| Ingress | W10 |
| Dispatcher / Passive Exposure | W11 |
| SafePoint / ReleaseRecycle | W12 |
| Eviction / TimeRange | W13 |
| Communication Bindings | W14 |
| Integrated Smoke / Compliance | W15 |

## First Integration Thread

```text
capacity profile
→ container
→ registry
→ bundle/moderator
→ waiting list
→ round manager
→ dispatch/ingress refs
→ reference supply
→ ingress / dispatcher
→ safe-point/recycle
→ eviction profile
→ communication binding
```

## Current Scope

This suite verifies compilation and boundary-safe composition of skeleton types.
It does not verify production runtime behavior.

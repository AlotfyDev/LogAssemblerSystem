# TRACEABILITY NOTES — CME-ARCH-PACK-05

## 1. Source Basis

This package builds on:

- CME-ARCH-PACK-00 holistic boundary positioning.
- CME-ARCH-PACK-02 dispatch cycle and waiting-list model.
- CME-ARCH-PACK-03 reference validity.
- CME-ARCH-PACK-04 dispatch exposure and release state.
- The project decision that the engine is pre-bridge write-side, not read-side receiver lifecycle.

## 2. Preserved Decisions

1. Dispatcher is final pre-bridge circulation actor.
2. Dispatch output is exposure, not final delivery.
3. Passive pull is default.
4. Push is optional profile.
5. Bridge owns bridge-side transfer semantics.
6. Read-side profile may own failed-dispatch/retry/delay.
7. Bridge drain assumption failure is a diagnostic/delegation event, not automatic pre-bridge retry ownership.

## 3. Boundary Anti-Collapse Rules

| Protected Meaning | Must Not Collapse Into |
|---|---|
| Dispatcher | Bridge Orchestrator |
| Dispatch Exposure | Final Delivery |
| Bridge-Facing Adapter | Receiver |
| Passive Pull | Persistence |
| Pre-Bridge Profile | Read-Side Profile |
| Bridge Drain Diagnostic | Retry Engine |

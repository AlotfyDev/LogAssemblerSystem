# DEFERRED DECISIONS — CME-ARCH-PACK-08

## 1. Critical Before First Wave

1. `TNextRefToken` shape.
2. `TContainerRef` necessity.
3. registry/profile generation tokens.
4. safe-point placement: shared root vs component-local.
5. report placement: local vs central diagnostics.

## 2. Deferred Beyond First Wave

1. push dispatch.
2. read-side failed-dispatch list.
3. receiver retry.
4. policy assignment integration.
5. persistence/audit export.
6. central diagnostics collector.

## 3. Implementation Deferral Rule

A deferred decision must not be silently implemented.
It must either remain absent or appear behind an explicit profile/placeholder.

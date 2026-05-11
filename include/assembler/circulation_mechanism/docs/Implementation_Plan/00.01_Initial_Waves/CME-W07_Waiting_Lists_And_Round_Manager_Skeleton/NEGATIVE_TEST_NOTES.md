# CME-W07 Negative / Anti-Collapse Notes

This wave protects the following rules:

1. Waiting list entry is a container-index candidate, not payload storage.
2. Ingress waiting list rejects dispatch-only states.
3. Dispatch waiting list rejects ingress-only states.
4. Closed rounds reject admission.
5. RoundManager does not calculate references.
6. RoundManager does not mutate bridge/read-side behavior.

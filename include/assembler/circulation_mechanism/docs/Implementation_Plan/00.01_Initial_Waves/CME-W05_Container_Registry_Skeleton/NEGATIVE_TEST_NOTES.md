# CME-W05 Negative / Anti-Collapse Notes

This wave protects the following rules:

1. Registry index is not a direct mutable external pointer.
2. Registry view is read-only.
3. Registry does not create container topology; BundleAgent owns topology.
4. Registry does not decide waiting-list eligibility; RoundManager owns that.
5. Registry does not calculate references; ReferencePrecalculator owns locating.
6. Registry is not a downstream registry/persistence layer.

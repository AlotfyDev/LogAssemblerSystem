# Deferred / Review Notes — CME-W15

## 1. TContainerTimeRange Ownership Convergence

During integrated compilation, W04 and W13 both expose a `TContainerTimeRange` skeleton:

```text
W04: container/TContainerTimeRange.hpp
W13: eviction/TContainerTimeRange.hpp
```

Current handling:

```text
- W04 remains the container-owned time-range skeleton.
- W13 remains covered by the anti-collapse compliance test and its own W13 smoke test.
- The full integrated smoke test avoids including both aggregate headers together until ownership/naming is converged.
```

Required follow-up:

```text
Decide whether TContainerTimeRange is owned by:
1. container/
2. eviction/
3. shared time_range/ or metadata/
4. container/ with eviction view/policy importing it
```

Recommended direction:

```text
container/ owns TContainerTimeRange.
eviction/ owns TEvictionCandidate and policies using container-owned time range.
```

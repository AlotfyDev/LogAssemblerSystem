# Canonical Responsibility & Obligation Matrix V2.1
## Closure-Covered Edition

### 0. Purpose
This matrix upgrades Batch 3 from raw system-level responsibilities into a closure-covered responsibility and obligation model derived from Canonical Contract Matrix V2, Unified Assembler Taxonomy, and gap/closure coverage.

### 1. Count Summary
| Category | Count |
|---|---:|
| Responsibility families | 8 |
| Top-level canonical responsibilities | 49 |
| Delivery-cycle flag sub-responsibilities | 7 |
| Detailed feedback report sub-responsibilities | 5 |
| Top-level canonical obligations | 49 |
| Delivery-cycle flag sub-obligations | 7 |
| Detailed feedback report sub-obligations | 5 |
| Covered gaps | 7 / 7 |

### 2. Key Corrections
1. `G-003` is split into delivery-cycle flags and detailed dispatcher feedback reports.
2. `G-004` creates no new responsibility because Timestamp Stabilizer is already promoted into the taxonomy as `E-INT-008` and covered by timestamp responsibilities.
3. `G-006` is represented through the queue-as-container terminology correction: queue is the container; there is no separate runtime container above queue.

### 3. Responsibility Families
| Family ID | Family Name |
|---|---|
| RSP-FAM-001 | Ingress Responsibilities |
| RSP-FAM-002 | Policy Responsibilities |
| RSP-FAM-003 | Metadata / Preparation Responsibilities |
| RSP-FAM-004 | Operational / Scaling Responsibilities |
| RSP-FAM-005 | Registry / Dispatcher Responsibilities |
| RSP-FAM-006 | Envelope Carrier Responsibilities |
| RSP-FAM-007 | Boundary / Exclusion Responsibilities |
| RSP-FAM-008 | Runtime State Responsibilities |

### 4. Responsibilities and Obligations
See the CSV files for the queryable matrix:
- `responsibilities_v2_1.csv`
- `obligations_v2_1.csv`
- `responsibility_obligation_links_v2_1.csv`
- `coverage_register_v2_1.csv`

### 5. Final Statement
This V2.1 matrix remains within Batch 3 scope. It derives responsibilities and obligations and identifies delegation candidates, but does not perform final responsibility assignment. Final assignment is reserved for Batch 4.

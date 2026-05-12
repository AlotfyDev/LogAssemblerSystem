# Assembler Taxonomy CSV Index Schema

## 0.1 Purpose
This package provides queryable CSV indexes for the unified Assembler Architectural Taxonomy.

## 0.2 Design Rule
The CSV files are compact indexes for fast filtering, counting, joins, and hierarchy traversal. They complement the modular JSON files, not replace them.

## 1. File Schemas

### 1.1 `00.01_layers_index.csv`
Layer-level index.

| Column | Meaning | Query Use |
|---|---|---|
| `layer_id` | Canonical layer ID | Join from members |
| `layer_order` | Numeric layer order | Sort hierarchy |
| `layer_name` | Human-readable layer name | Display |
| `layer_type` | Coarse type | Filter by category |
| `purpose` | Layer purpose | Search |
| `member_count` | Expected count | Validation/counting |
| `parent_id` | Reserved parent link | Future nesting |
| `hierarchy_path` | Stable path | Sort/tree traversal |
| `query_tags` | Search tags | Free-text filtering |

### 1.2 `00.02_members_index.csv`
Unified member index.

| Column | Meaning | Query Use |
|---|---|---|
| `member_id` | Canonical member ID | Primary key |
| `member_name` | Human-readable name | Display/search |
| `layer_id` | Parent layer | Join to layers |
| `layer_order` | Parent order | Sort |
| `member_type` | Entity/object/family type | Filter |
| `plane_or_family` | Plane, family, doctrine category | Filter |
| `role` | Compact role | Search |
| `notes` | Canonical note | Reading context |
| `parent_id` | Reserved parent/specialization | Future hierarchy |
| `hierarchy_path` | Stable path | Tree traversal |
| `query_tags` | Keywords | Search |

### 1.3 `00.03_relations_index.csv`
Unified relation index.

| Column | Meaning | Query Use |
|---|---|---|
| `relation_id` | Canonical relation ID | Primary key |
| `relation_family_id` | Parent relation family | Filter/group |
| `source_id` | Source node | Join to members/relations |
| `source_layer_id` | Source layer if resolvable | Filter |
| `target_id` | Target node | Join to members/relations |
| `target_layer_id` | Target layer if resolvable | Filter |
| `direction` | inbound/outbound/internal/derived/applies/none | Filter |
| `relation_type` | boundary/policy/carrier/runtime/waiting/contract/doctrine | Filter |
| `object_or_subject` | Payload/object/topic | Search |
| `meaning` | Compact semantic meaning | Search |
| `hierarchy_path` | Stable relation path | Tree traversal |
| `query_tags` | Keywords | Search |

### 1.4 `00.04_contracts_index.csv`
Canonical contract index.

| Column | Meaning | Query Use |
|---|---|---|
| `contract_id` | Canonical contract ID | Primary key |
| `contract_family_id` | Parent contract family | Join/filter |
| `contract_name` | Human-readable name | Display/search |
| `direction` | Contract direction | Filter |
| `object_or_subject` | Governed object/payload | Search |
| `role` | Contract role | Search |
| `hierarchy_path` | Stable contract path | Tree traversal |
| `query_tags` | Keywords | Search |

### 1.5 `00.05_counts_index.csv`
Top-level count summary.

| Column | Meaning |
|---|---|
| `metric_id` | Metric ID |
| `category` | Counted category |
| `count_value` | Numeric count |
| `source_file` | CSV used for count |

## 2. Query Examples

### 2.1 Count all internal entities
Filter `00.02_members_index.csv` where `member_type = internal_entity`.

### 2.2 Find queue-related taxonomy elements
Search `query_tags` for `queue` across `members`, `relations`, and `contracts`.

### 2.3 Find all outbound external boundary relations
Filter `00.03_relations_index.csv` where `relation_family_id = REL-FAM-001` and `direction = outbound`.

### 2.4 Find all contract families
Filter `00.02_members_index.csv` where `member_type = contract_family`.

### 2.5 Trace a relation hierarchy
Use `relation_family_id` to group, then join `source_id` and `target_id` to `00.02_members_index.csv`.

## 3. Growth Policy
Future batches should add rows or new specialized CSVs without changing existing canonical IDs.

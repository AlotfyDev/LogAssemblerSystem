08_assembler_skills/
│
├── 00_PACKAGE_MANIFEST.json
├── 01_SKILLS_RELEASE_README.md
├── 02_SKILLS_ARCHITECTURE_OVERVIEW.md
├── 03_SKILLS_FILE_MAP.csv
├── 04_SKILLS_SCHEMA.md
│
├── 00_shared_canonical_kernel/
│   ├── 00.01_CANONICAL_KERNEL.md
│   ├── 00.02_ID_GRAMMAR_AND_JOIN_KEYS.md
│   ├── 00.03_SOURCE_PRIORITY_AND_AUTHORITY.md
│   ├── 00.04_ANTI_COLLAPSE_RULES.md
│   └── 00.05_VALIDATION_BASELINE.md
│
├── 01_content_editor_skill/
│   ├── 01.00_CONTENT_EDITOR_SKILL_MANIFEST.json
│   │
│   ├── core/
│   │   ├── 01.01_CONTENT_EDITOR_CORE_SPEC.md
│   │   ├── 01.02_CHANGE_CLASSIFICATION.md
│   │   ├── 01.03_IMPACT_ANALYSIS_PROTOCOL.md
│   │   ├── 01.04_PATCH_GENERATION_PROTOCOL.md
│   │   ├── 01.05_PROPAGATION_RULES.md
│   │   └── 01.06_EDITOR_VALIDATION_CHECKLIST.md
│   │
│   ├── cli/
│   │   ├── 01.07_EDITOR_CLI_SPEC.md
│   │   ├── 01.08_EDITOR_COMMANDS.md
│   │   ├── 01.09_EDITOR_COMMAND_IO_SCHEMA.md
│   │   └── 01.10_EDITOR_CLI_EXAMPLES.md
│   │
│   └── integrations/
│       ├── codex/
│       │   └── CODEX_EDITOR_ADAPTER.md
│       ├── kilo_code/
│       │   └── KILO_CODE_EDITOR_ADAPTER.md
│       ├── opencode/
│       │   └── OPENCODE_EDITOR_ADAPTER.md
│       ├── github/
│       │   └── GITHUB_EDITOR_ADAPTER.md
│       ├── google_drive/
│       │   └── GOOGLE_DRIVE_EDITOR_ADAPTER.md
│       └── local_runtime/
│           └── LOCAL_EDITOR_ADAPTER.md
│
├── 02_query_expert_skill/
│   ├── 02.00_QUERY_EXPERT_SKILL_MANIFEST.json
│   │
│   ├── core/
│   │   ├── 02.01_QUERY_EXPERT_CORE_SPEC.md
│   │   ├── 02.02_QUERY_ROUTING_PROTOCOL.md
│   │   ├── 02.03_JOIN_AND_TRACE_PROTOCOL.md
│   │   ├── 02.04_EVIDENCE_OUTPUT_PROTOCOL.md
│   │   ├── 02.05_ANSWER_GUARDS.md
│   │   └── 02.06_QUERY_VALIDATION_CHECKLIST.md
│   │
│   ├── cli/
│   │   ├── 02.07_QUERY_CLI_SPEC.md
│   │   ├── 02.08_QUERY_COMMANDS.md
│   │   ├── 02.09_QUERY_COMMAND_IO_SCHEMA.md
│   │   └── 02.10_QUERY_CLI_EXAMPLES.md
│   │
│   └── integrations/
│       ├── codex/
│       │   └── CODEX_QUERY_ADAPTER.md
│       ├── kilo_code/
│       │   └── KILO_CODE_QUERY_ADAPTER.md
│       ├── opencode/
│       │   └── OPENCODE_QUERY_ADAPTER.md
│       ├── github/
│       │   └── GITHUB_QUERY_ADAPTER.md
│       ├── google_drive/
│       │   └── GOOGLE_DRIVE_QUERY_ADAPTER.md
│       └── local_runtime/
│           └── LOCAL_QUERY_ADAPTER.md
│
└── 03_execution_contracts/
    ├── 03.01_CORE_TO_CLI_CONTRACT.md
    ├── 03.02_CLI_COMMAND_GRAMMAR.md
    ├── 03.03_CLI_TO_ADAPTER_CONTRACT.md
    ├── 03.04_ADAPTER_CAPABILITY_MATRIX.csv
    ├── 03.05_ADAPTER_LIFECYCLE.md
    ├── 03.06_ERROR_AND_LIMITATION_MODEL.md
    └── 03.07_INTEGRATION_VALIDATION_PROTOCOL.md
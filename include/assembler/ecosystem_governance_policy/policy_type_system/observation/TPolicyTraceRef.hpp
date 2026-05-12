#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTraceRef.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyTraceRef provides a compact correlation reference for policy observation records. It supports traceability without importing tracing frameworks or external observability systems.
 *
 * Why this file exists in W05:
 *   W05 observation requires a way to correlate audit records and evidence, but the Policy Type System must not become an OpenTelemetry exporter or logging backend.
 *
 * Relationship to previous waves:
 *   - W01 identity and provenance can pair with trace references.
 *   - W03 replacement and W04 lifecycle events may later be correlated through this reference.
 *
 * Relationship to future waves:
 *   - W06 realization binding may include trace references when describing mechanism-binding observations.
 *   - W07 policy graph views may expose trace references as part of observation/audit substructure.
 *   - W09 TPolicy aggregate may surface trace references safely.
 *
 * Explicit non-responsibilities:
 *   TPolicyTraceRef is not OpenTelemetry, not a span, not a logging framework record, not a distributed trace implementation, and not a communication-context correlation protocol.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

struct TPolicyTraceRef final
{
    using token_type = std::uint64_t;

    token_type correlation{0};
    token_type sequence{0};

    constexpr TPolicyTraceRef() noexcept = default;
    constexpr TPolicyTraceRef(token_type c, token_type s = 0) noexcept : correlation(c), sequence(s) {}

    [[nodiscard]] static constexpr TPolicyTraceRef Empty() noexcept { return TPolicyTraceRef{}; }
    [[nodiscard]] constexpr bool IsPresent() const noexcept { return correlation != 0; }

    friend constexpr bool operator==(TPolicyTraceRef lhs, TPolicyTraceRef rhs) noexcept
    {
        return lhs.correlation == rhs.correlation && lhs.sequence == rhs.sequence;
    }

    friend constexpr bool operator!=(TPolicyTraceRef lhs, TPolicyTraceRef rhs) noexcept { return !(lhs == rhs); }
};

} // namespace assembler::ecosystem_governance::policy_type_system

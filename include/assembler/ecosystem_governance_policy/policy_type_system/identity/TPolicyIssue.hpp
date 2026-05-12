#pragma once

#include <cstdint>
#include "TPolicyStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyIssue.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyIssue is the primitive diagnostic carrier for policy identity-layer
 *   problems. It allows early waves to report why an identity primitive,
 *   version, scope, source, or provenance descriptor is invalid, incomplete, or
 *   unsupported without introducing the later observation/audit subsystem.
 *
 * Why this file exists in W01:
 *   Policy identity must be traceable and reviewable. Even at the primitive
 *   level, invalid identity values must be explainable. This file provides the
 *   smallest issue carrier needed by TPolicyResult and future validation
 *   helpers.
 *
 * Relationship to other files:
 *   - TPolicyStatus classifies the issue outcome.
 *   - TPolicyResult may include one TPolicyIssue.
 *   - TPolicyId, TPolicyFamilyId, TPolicyVersion, TPolicyScope, TPolicySource,
 *     and TPolicyProvenance can all be subjects of identity-layer issues.
 *
 * Relationship to future waves:
 *   - W05 observation/audit may convert or include identity issues as evidence.
 *   - W07 graph invariant reports may use richer issue types; this primitive
 *     issue remains suitable for W01-level concerns.
 *
 * Explicit non-responsibilities:
 *   TPolicyIssue is not an audit trail, not a log record, not an exception, not
 *   a telemetry event, and not a registry diagnostic. It is a small value object
 *   for identity-layer reporting.
 */
struct TPolicyIssue final
{
    using code_type = std::uint32_t;

    TPolicyStatus status{TPolicyStatus::unknown};
    code_type code{0};

    constexpr TPolicyIssue() noexcept = default;
    constexpr TPolicyIssue(TPolicyStatus s, code_type c = 0) noexcept : status(s), code(c) {}

    [[nodiscard]] constexpr bool HasIssue() const noexcept
    {
        return status != TPolicyStatus::unknown && status != TPolicyStatus::valid;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

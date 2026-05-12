#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyKind.hpp

 * Wave: EG-POL-W12_Policy_Family_And_Scope
 * Domain: ecosystem_governance / policy_type_system / family
 *
 * Architectural boundary:
 *   W12 is the first implementation wave after Phase A architecture completion.
 *   It introduces the policy-family and policy-scope vocabulary needed before
 *   target capability contracts, compatibility evaluators, assignment lifecycle
 *   implementation, publication/versioning implementation, runtime readiness,
 *   or any future TPolicyRealizer. The wave remains descriptive and
 *   non-executing.
 *
 * Relationship to prior waves:
 *   - W01 provides primitive policy identity, including TPolicyFamilyId and
 *     TPolicyScope.
 *   - W09 provides the TPolicy aggregate, which may later contain or reference
 *     family profile information.
 *   - W10 provides assignment basics; W12 does not activate assignments.
 *   - W11 provides registry basics; W12 does not become a registry.
 *
 * Relationship to Phase A architecture:
 *   This wave implements the smallest code-level vocabulary derived from
 *   EG-POL-ARCH-001_Policy_Family_Taxonomy_And_Scope_Model and prepares later
 *   implementation of EG-POL-ARCH-002 and EG-POL-ARCH-003 without crossing into
 *   target invocation, policy realization, or runtime execution.
 *
 * Explicit non-responsibilities:
 *   This file does not implement target capability surfaces, target ownership,
 *   compatibility evaluation against concrete targets, assignment lifecycle,
 *   policy source ingestion, registry persistence, policy realization, runtime
 *   scheduling, telemetry, logging, or material circulation behavior.
 *
 * Current implementation posture:
 *   The current code is a C++17 header-only foundational block. The opening
 *   documentation describes the full architectural responsibility even when the
 *   code intentionally exposes only conservative value carriers and simple
 *   helper functions.

 * File responsibility:
 *   TPolicyFamilyKind classifies the broad semantic category of a policy
 *   family. It is intentionally coarser than a concrete policy type and much
 *   coarser than a policy instance. Later compatibility matrices may use this
 *   category to decide which scope vocabulary, target-kind families,
 *   replacement expectations, and observation requirements are even eligible.
 */
enum class TPolicyFamilyKind : std::uint8_t
{
    unspecified = 0,
    preparation = 1,
    admission = 2,
    runtime_coordination = 3,
    dispatch = 4,
    communication = 5,
    port = 6,
    addon = 7,
    replacement = 8,
    lifecycle = 9,
    diagnostic = 10,
    governance = 11,
    execution_readiness = 12,
    compliance = 13,
    custom = 255
};

[[nodiscard]] constexpr bool IsKnownPolicyFamilyKind(TPolicyFamilyKind kind) noexcept
{
    return kind != TPolicyFamilyKind::unspecified;
}

[[nodiscard]] constexpr bool IsRuntimeSensitivePolicyFamilyKind(TPolicyFamilyKind kind) noexcept
{
    return kind == TPolicyFamilyKind::runtime_coordination ||
           kind == TPolicyFamilyKind::dispatch ||
           kind == TPolicyFamilyKind::communication ||
           kind == TPolicyFamilyKind::port ||
           kind == TPolicyFamilyKind::execution_readiness;
}

[[nodiscard]] constexpr bool IsGovernancePolicyFamilyKind(TPolicyFamilyKind kind) noexcept
{
    return kind == TPolicyFamilyKind::governance ||
           kind == TPolicyFamilyKind::compliance ||
           kind == TPolicyFamilyKind::diagnostic;
}

} // namespace assembler::ecosystem_governance::policy_type_system

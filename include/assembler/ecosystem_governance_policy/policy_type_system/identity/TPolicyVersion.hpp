#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyVersion.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyVersion is the primitive version descriptor for a policy identity.
 *   It exists to support safe replacement, registry distinction, auditability,
 *   and future compatibility checks without requiring a full policy aggregate.
 *
 * Why this file exists in W01:
 *   The Policy Object taxonomy requires policy versioning as part of minimum
 *   identity semantics. Replacement discipline cannot be designed safely unless
 *   a policy can be distinguished from another policy in the same family and
 *   scope by version or generation.
 *
 * Relationship to other files:
 *   - TPolicyId identifies the concrete policy.
 *   - TPolicyFamilyId identifies the semantic family.
 *   - TPolicyScope identifies the intended governance boundary.
 *   - TPolicySource and TPolicyProvenance may explain how a version originated.
 *   - TPolicyIssue and TPolicyResult may report invalid version combinations.
 *
 * Relationship to future waves:
 *   - W03 replacement rules may compare versions.
 *   - W05 audit records may record activation or replacement from one version
 *     to another.
 *   - W07 graph invariants may require version-bearing identity structure.
 *   - W10/W11 assignment and registry may use version as part of lookup or
 *     compatibility decisions.
 *
 * Explicit non-responsibilities:
 *   TPolicyVersion is not a compatibility matrix, not a replacement plan, not a
 *   source-control revision, and not a runtime lifecycle state. It only carries
 *   semantic version-like identity.
 *
 * Current implementation note:
 *   W01 uses major/minor/patch numeric fields and simple comparison operators.
 *   Later waves may add generation, epoch, build metadata, or external catalog
 *   version linkage if needed.
 */
struct TPolicyVersion final
{
    using value_type = std::uint32_t;

    value_type major{0};
    value_type minor{0};
    value_type patch{0};

    constexpr TPolicyVersion() noexcept = default;
    constexpr TPolicyVersion(value_type maj, value_type min, value_type pat) noexcept
        : major(maj), minor(min), patch(pat) {}

    [[nodiscard]] static constexpr TPolicyVersion Zero() noexcept { return TPolicyVersion{}; }
    [[nodiscard]] constexpr bool IsZero() const noexcept { return major == 0 && minor == 0 && patch == 0; }

    friend constexpr bool operator==(TPolicyVersion lhs, TPolicyVersion rhs) noexcept
    {
        return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch;
    }

    friend constexpr bool operator!=(TPolicyVersion lhs, TPolicyVersion rhs) noexcept { return !(lhs == rhs); }

    friend constexpr bool operator<(TPolicyVersion lhs, TPolicyVersion rhs) noexcept
    {
        return (lhs.major < rhs.major) ||
               (lhs.major == rhs.major && lhs.minor < rhs.minor) ||
               (lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch < rhs.patch);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

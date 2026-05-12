#pragma once

#include "TPolicyValidationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyResult.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyBuildResult.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicyBuildResult is the result carrier for W09 aggregate construction or
 *   build-request validation. It combines the primitive policy result from W01
 *   with the aggregate validation report introduced in W09.
 *
 * Why this file exists in W09:
 *   TPolicy construction may be partially valid at the identity level while not
 *   yet structurally complete as a full policy aggregate. This file allows the
 *   implementation to distinguish build acceptance from full structural
 *   completeness without inventing an assignment result or registry result.
 *
 * Relationship to previous waves:
 *   - W01 provides TPolicyResult.
 *   - W09 provides TPolicyValidationReport because aggregate completeness can
 *     only be assessed once prior foundations are composed.
 *
 * Relationship to other files in this wave:
 *   - TPolicy may produce TPolicyBuildResult from a build request.
 *   - TPolicyBuildRequest supplies the initial input.
 *
 * Relationship to future waves:
 *   - W10 assignment results and W11 registry lookup results may be distinct
 *     types and must not collapse into this build result.
 *
 * Explicit non-responsibilities:
 *   TPolicyBuildResult is not a TPolicy object, not an assignment result, not a
 *   registry result, not a realization result, not a traversal result, and not a
 *   persistence acknowledgement.
 *
 * Current implementation note:
 *   W09 keeps this value compact. Future waves may add richer diagnostics while
 *   preserving the separation between build validation and execution behavior.
 */
struct TPolicyBuildResult final
{
    TPolicyResult result{};
    TPolicyValidationReport validation{};

    [[nodiscard]] constexpr bool Accepted() const noexcept
    {
        return result.Ok();
    }

    [[nodiscard]] constexpr bool StructurallyComplete() const noexcept
    {
        return validation.IsStructurallyComplete();
    }

    [[nodiscard]] static constexpr TPolicyBuildResult FromValidation(TPolicyValidationReport report) noexcept
    {
        TPolicyBuildResult out{};
        out.validation = report;
        out.result = report.IsStructurallyComplete()
            ? TPolicyResult::Success()
            : TPolicyResult::Failure(TPolicyStatus::incomplete, report.MissingMask());
        return out;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system

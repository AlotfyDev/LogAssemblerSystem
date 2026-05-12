#pragma once

#include <cstdint>
#include "TPolicyRealizationBindingId.hpp"
#include "TPolicyRealizationMode.hpp"
#include "TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyResult.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationResult.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationResult is a small result carrier for W06 descriptor and
 *   binding construction/validation outcomes. It reports whether a realization
 *   binding descriptor is structurally acceptable, not whether realization was
 *   executed against a target.
 *
 * Why this file exists in W06:
 *   W06 introduces several descriptive binding carriers. A lightweight result
 *   type keeps validation and smoke-test behavior explicit while preserving the
 *   boundary that this wave does not implement a realizer or target invocation.
 *
 * Relationship to previous waves:
 *   - W01 provides TPolicyResult as a primitive success/failure carrier.
 *   - W06 specializes that result around realization binding context.
 *
 * Relationship to other files in this wave:
 *   - It references TPolicyRealizationBindingId, TPolicyRealizationMode, and
 *     TPolicyTargetKind to describe the result subject.
 *
 * Relationship to future waves:
 *   - W09 TPolicy validation may translate realization binding checks into
 *     aggregate validation reports.
 *   - W10 assignment may use similar result vocabulary for assignment checks.
 *
 * Explicit non-responsibilities:
 *   TPolicyRealizationResult is not execution output, not target response, not
 *   assignment result, not registry lookup result, and not observation/audit
 *   storage.
 *
 * Current implementation note:
 *   This file is intentionally small. It helps smoke tests express validity
 *   without pulling in future validation-report types.
 */
struct TPolicyRealizationResult final
{
    TPolicyResult base{};
    TPolicyRealizationBindingId binding_id{};
    TPolicyRealizationMode mode{TPolicyRealizationMode::unknown};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    std::uint32_t detail_code{0};

    constexpr TPolicyRealizationResult() noexcept = default;

    constexpr TPolicyRealizationResult(
        TPolicyResult result,
        TPolicyRealizationBindingId id,
        TPolicyRealizationMode realization_mode = TPolicyRealizationMode::unknown,
        TPolicyTargetKind kind = TPolicyTargetKind::unknown,
        std::uint32_t detail = 0) noexcept
        : base(result), binding_id(id), mode(realization_mode), target_kind(kind), detail_code(detail) {}

    [[nodiscard]] constexpr bool Succeeded() const noexcept { return base.Ok(); }
    [[nodiscard]] constexpr bool Failed() const noexcept { return !base.Ok(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system

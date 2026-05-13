#pragma once

#include <string_view>

/**
 * @file TBindingExecutionAssumption.hpp
 * @brief Execution-assumption vocabulary for ASCC binding composition metadata.
 *
 * @section ascc_comp_w04 Purpose
 * Execution assumption describes what kind of runtime support a binding shape
 * expects. It is declarative metadata only; it does not create schedulers,
 * bridge runners, worker pools, endpoint invokers, or pipeline profiles.
 */

namespace assembler::communication_context
{
    enum class TBindingExecutionAssumption
    {
        unknown,
        model_only,
        runtime_invocation_required,
        single_writer_compatible,
        multi_instance_compatible,
        bounded_step,
        external_scheduler_required
    };

    [[nodiscard]] constexpr bool requires_runtime_invocation(
        TBindingExecutionAssumption assumption) noexcept
    {
        return assumption == TBindingExecutionAssumption::runtime_invocation_required
            || assumption == TBindingExecutionAssumption::external_scheduler_required;
    }

    [[nodiscard]] constexpr bool is_model_only(
        TBindingExecutionAssumption assumption) noexcept
    {
        return assumption == TBindingExecutionAssumption::model_only;
    }

    [[nodiscard]] constexpr bool is_single_writer_compatible(
        TBindingExecutionAssumption assumption) noexcept
    {
        return assumption == TBindingExecutionAssumption::single_writer_compatible;
    }

    [[nodiscard]] constexpr bool supports_multiple_instances(
        TBindingExecutionAssumption assumption) noexcept
    {
        return assumption == TBindingExecutionAssumption::multi_instance_compatible;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingExecutionAssumption assumption) noexcept
    {
        switch (assumption)
        {
            case TBindingExecutionAssumption::unknown: return "unknown";
            case TBindingExecutionAssumption::model_only: return "model_only";
            case TBindingExecutionAssumption::runtime_invocation_required: return "runtime_invocation_required";
            case TBindingExecutionAssumption::single_writer_compatible: return "single_writer_compatible";
            case TBindingExecutionAssumption::multi_instance_compatible: return "multi_instance_compatible";
            case TBindingExecutionAssumption::bounded_step: return "bounded_step";
            case TBindingExecutionAssumption::external_scheduler_required: return "external_scheduler_required";
        }

        return "unknown";
    }
}

#pragma once

#include <string_view>

namespace assembler::communication_context
{
    enum class TAsccOperationMode
    {
        unknown,
        model_step,
        bounded_model_run,
        model_step_with_endpoint_invocation,
        diagnostic_dry_run
    };

    [[nodiscard]] constexpr std::string_view to_string(TAsccOperationMode mode) noexcept
    {
        switch (mode)
        {
            case TAsccOperationMode::unknown: return "unknown";
            case TAsccOperationMode::model_step: return "model_step";
            case TAsccOperationMode::bounded_model_run: return "bounded_model_run";
            case TAsccOperationMode::model_step_with_endpoint_invocation: return "model_step_with_endpoint_invocation";
            case TAsccOperationMode::diagnostic_dry_run: return "diagnostic_dry_run";
        }

        return "unknown";
    }
}

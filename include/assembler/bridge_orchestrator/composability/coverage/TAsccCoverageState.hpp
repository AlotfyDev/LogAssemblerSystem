#pragma once

#include <string_view>

/**
 * @file TAsccCoverageState.hpp
 * @brief Coverage state for ASCC composability requirements and capabilities.
 */

namespace assembler::communication_context
{
    enum class TAsccCoverageState
    {
        unknown,
        covered,
        partially_covered,
        missing,
        intentionally_deferred,
        deferred_to_integration,
        deferred_to_pipeline_composer,
        deferred_to_policy_layer,
        out_of_scope
    };

    [[nodiscard]] constexpr bool is_covered(TAsccCoverageState state) noexcept
    {
        return state == TAsccCoverageState::covered;
    }

    [[nodiscard]] constexpr bool is_missing(TAsccCoverageState state) noexcept
    {
        return state == TAsccCoverageState::missing;
    }

    [[nodiscard]] constexpr bool is_deferred(TAsccCoverageState state) noexcept
    {
        return state == TAsccCoverageState::intentionally_deferred
            || state == TAsccCoverageState::deferred_to_integration
            || state == TAsccCoverageState::deferred_to_pipeline_composer
            || state == TAsccCoverageState::deferred_to_policy_layer
            || state == TAsccCoverageState::out_of_scope;
    }

    [[nodiscard]] constexpr bool blocks_core_readiness(TAsccCoverageState state) noexcept
    {
        return state == TAsccCoverageState::missing;
    }

    [[nodiscard]] constexpr std::string_view to_string(TAsccCoverageState state) noexcept
    {
        switch (state)
        {
            case TAsccCoverageState::unknown: return "unknown";
            case TAsccCoverageState::covered: return "covered";
            case TAsccCoverageState::partially_covered: return "partially_covered";
            case TAsccCoverageState::missing: return "missing";
            case TAsccCoverageState::intentionally_deferred: return "intentionally_deferred";
            case TAsccCoverageState::deferred_to_integration: return "deferred_to_integration";
            case TAsccCoverageState::deferred_to_pipeline_composer: return "deferred_to_pipeline_composer";
            case TAsccCoverageState::deferred_to_policy_layer: return "deferred_to_policy_layer";
            case TAsccCoverageState::out_of_scope: return "out_of_scope";
        }

        return "unknown";
    }
}

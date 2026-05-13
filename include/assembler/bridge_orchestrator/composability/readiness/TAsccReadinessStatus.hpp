#pragma once

#include <string_view>

/**
 * @file TAsccReadinessStatus.hpp
 * @brief Generic ASCC readiness status vocabulary.
 *
 * @section ascc_comp_w06 Purpose
 * W06 introduces ASCC-level readiness and evidence views that aggregate
 * participant, binding, protocol, session, and bridge model evidence without
 * executing endpoints, protocols, sessions, or pipeline composition.
 */

namespace assembler::communication_context
{
    enum class TAsccReadinessStatus
    {
        unknown,
        ready,
        not_ready,
        blocked,
        degraded,
        deferred,
        out_of_scope
    };

    [[nodiscard]] constexpr bool is_ready(TAsccReadinessStatus status) noexcept
    {
        return status == TAsccReadinessStatus::ready;
    }

    [[nodiscard]] constexpr bool is_blocking_readiness_status(
        TAsccReadinessStatus status) noexcept
    {
        return status == TAsccReadinessStatus::blocked
            || status == TAsccReadinessStatus::not_ready;
    }

    [[nodiscard]] constexpr bool is_deferred_readiness_status(
        TAsccReadinessStatus status) noexcept
    {
        return status == TAsccReadinessStatus::deferred
            || status == TAsccReadinessStatus::out_of_scope;
    }

    [[nodiscard]] constexpr bool is_known_readiness_status(
        TAsccReadinessStatus status) noexcept
    {
        return status != TAsccReadinessStatus::unknown;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccReadinessStatus status) noexcept
    {
        switch (status)
        {
            case TAsccReadinessStatus::unknown: return "unknown";
            case TAsccReadinessStatus::ready: return "ready";
            case TAsccReadinessStatus::not_ready: return "not_ready";
            case TAsccReadinessStatus::blocked: return "blocked";
            case TAsccReadinessStatus::degraded: return "degraded";
            case TAsccReadinessStatus::deferred: return "deferred";
            case TAsccReadinessStatus::out_of_scope: return "out_of_scope";
        }

        return "unknown";
    }
}

#pragma once

#include <string_view>

namespace assembler::communication_context
{
    enum class TAsccComponentReadinessStatus
    {
        unknown,
        ready,
        not_ready,
        blocked,
        degraded,
        deferred
    };

    [[nodiscard]] constexpr bool is_ready_status(
        TAsccComponentReadinessStatus status) noexcept
    {
        return status == TAsccComponentReadinessStatus::ready;
    }

    [[nodiscard]] constexpr bool is_blocking_status(
        TAsccComponentReadinessStatus status) noexcept
    {
        return status == TAsccComponentReadinessStatus::blocked
            || status == TAsccComponentReadinessStatus::not_ready;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccComponentReadinessStatus status) noexcept
    {
        switch (status)
        {
            case TAsccComponentReadinessStatus::unknown: return "unknown";
            case TAsccComponentReadinessStatus::ready: return "ready";
            case TAsccComponentReadinessStatus::not_ready: return "not_ready";
            case TAsccComponentReadinessStatus::blocked: return "blocked";
            case TAsccComponentReadinessStatus::degraded: return "degraded";
            case TAsccComponentReadinessStatus::deferred: return "deferred";
        }

        return "unknown";
    }
}

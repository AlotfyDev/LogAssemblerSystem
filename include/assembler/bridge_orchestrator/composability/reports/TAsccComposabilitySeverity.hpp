#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TAsccComposabilitySeverity.hpp
 * @brief Severity taxonomy for ASCC composability reports.
 */

namespace assembler::communication_context
{
    enum class TAsccComposabilitySeverity
    {
        unknown,
        info,
        warning,
        blocking,
        critical
    };

    [[nodiscard]] constexpr std::uint32_t severity_rank(
        TAsccComposabilitySeverity severity) noexcept
    {
        switch (severity)
        {
            case TAsccComposabilitySeverity::unknown: return 0u;
            case TAsccComposabilitySeverity::info: return 1u;
            case TAsccComposabilitySeverity::warning: return 2u;
            case TAsccComposabilitySeverity::blocking: return 3u;
            case TAsccComposabilitySeverity::critical: return 4u;
        }
        return 0u;
    }

    [[nodiscard]] constexpr bool is_blocking(
        TAsccComposabilitySeverity severity) noexcept
    {
        return severity == TAsccComposabilitySeverity::blocking
            || severity == TAsccComposabilitySeverity::critical;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccComposabilitySeverity severity) noexcept
    {
        switch (severity)
        {
            case TAsccComposabilitySeverity::unknown: return "unknown";
            case TAsccComposabilitySeverity::info: return "info";
            case TAsccComposabilitySeverity::warning: return "warning";
            case TAsccComposabilitySeverity::blocking: return "blocking";
            case TAsccComposabilitySeverity::critical: return "critical";
        }
        return "unknown";
    }
}

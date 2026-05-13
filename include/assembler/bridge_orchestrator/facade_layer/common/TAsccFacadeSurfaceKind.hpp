#pragma once

#include <string_view>

namespace assembler::communication_context
{
    enum class TAsccFacadeSurfaceKind
    {
        unknown,
        administrative,
        managerial,
        consuming,
        cross_surface
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccFacadeSurfaceKind kind) noexcept
    {
        switch (kind)
        {
            case TAsccFacadeSurfaceKind::unknown: return "unknown";
            case TAsccFacadeSurfaceKind::administrative: return "administrative";
            case TAsccFacadeSurfaceKind::managerial: return "managerial";
            case TAsccFacadeSurfaceKind::consuming: return "consuming";
            case TAsccFacadeSurfaceKind::cross_surface: return "cross_surface";
        }

        return "unknown";
    }
}

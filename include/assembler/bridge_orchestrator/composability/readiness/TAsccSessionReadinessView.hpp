#pragma once

#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccSessionReadinessView.hpp
 * @brief Read-only readiness projection for ASCC session availability.
 *
 * @section ascc_comp_w06 Purpose
 * This view describes whether session model participation is required,
 * available, and openable. It does not open, run, or close sessions.
 */

namespace assembler::communication_context
{
    struct TAsccSessionReadinessView final
    {
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool session_required{false};
        bool session_model_available{false};
        bool session_openable{false};
        std::string_view session_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && !session_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            if (!is_valid())
            {
                return false;
            }

            if (!session_required)
            {
                return status == TAsccReadinessStatus::ready
                    || status == TAsccReadinessStatus::out_of_scope;
            }

            return is_ready(status)
                && session_model_available
                && session_openable;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || (session_required && (!session_model_available || !session_openable));
        }

        [[nodiscard]] static constexpr TAsccSessionReadinessView make(
            TAsccReadinessStatus readiness_status,
            bool is_session_required,
            bool has_session_model,
            bool can_open_session,
            std::string_view name = "session_readiness") noexcept
        {
            return TAsccSessionReadinessView{
                readiness_status,
                is_session_required,
                has_session_model,
                can_open_session,
                name
            };
        }
    };
}

#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccEvidenceDimension.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccReadinessEvidenceRef.hpp
 * @brief Lightweight reference to readiness evidence produced by ASCC submodels.
 *
 * @section ascc_comp_w06 Purpose
 * Evidence references allow W06 reports to point at participant, binding,
 * protocol, session, bridge, diagnostic, or registry evidence without copying
 * or owning the source reports themselves.
 */

namespace assembler::communication_context
{
    struct TAsccReadinessEvidenceRef final
    {
        std::uint64_t evidence_id{0u};
        TAsccEvidenceDimension dimension{TAsccEvidenceDimension::unknown};
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        std::string_view source_component{};
        std::string_view source_wave{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return evidence_id != 0u
                && dimension != TAsccEvidenceDimension::unknown
                && status != TAsccReadinessStatus::unknown
                && !source_component.empty();
        }

        [[nodiscard]] constexpr bool is_ready_evidence() const noexcept
        {
            return is_valid() && is_ready(status);
        }

        [[nodiscard]] constexpr bool blocks_core_readiness() const noexcept
        {
            return is_valid() && is_blocking_readiness_status(status);
        }

        [[nodiscard]] constexpr bool is_deferred() const noexcept
        {
            return is_valid() && is_deferred_readiness_status(status);
        }

        [[nodiscard]] static constexpr TAsccReadinessEvidenceRef make(
            std::uint64_t id,
            TAsccEvidenceDimension evidence_dimension,
            TAsccReadinessStatus evidence_status,
            std::string_view source,
            std::string_view wave = {},
            std::string_view evidence_note = {}) noexcept
        {
            return TAsccReadinessEvidenceRef{
                id,
                evidence_dimension,
                evidence_status,
                source,
                wave,
                evidence_note
            };
        }
    };
}

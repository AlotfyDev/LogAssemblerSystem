#pragma once
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"

/**
 * @file TObligationTraitAudit.hpp
 * @brief Converts static obligation-trait availability into evidence.
 */
namespace assembler::communication_context {
    struct TObligationTraitAudit final {
        [[nodiscard]] static constexpr TObligationReport satisfied_trait(std::string_view name) noexcept {
            return TObligationReport::satisfied(TObligationSide::binding, name);
        }
        [[nodiscard]] static constexpr TObligationReport missing_trait(std::string_view name) noexcept {
            return TObligationReport::incomplete(TObligationSide::binding, name, "trait missing");
        }
    };
}

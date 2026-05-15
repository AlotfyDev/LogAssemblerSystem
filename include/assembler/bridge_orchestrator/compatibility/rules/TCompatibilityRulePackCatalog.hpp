#pragma once
#include "assembler/communication_context/compatibility/rules/TCompatibilityRuleSet.hpp"

/**
 * @file TCompatibilityRulePackCatalog.hpp
 * @brief Administrative catalog for compatibility rule packs.
 */
namespace assembler::communication_context {
    struct TCompatibilityRulePackCatalog final {
        bool strict_binding_pack_available{true};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return strict_binding_pack_available; }
        [[nodiscard]] static constexpr auto strict_binding_rules() noexcept { return TCompatibilityRuleSet<7>::strict_binding_rules(); }
    };
}

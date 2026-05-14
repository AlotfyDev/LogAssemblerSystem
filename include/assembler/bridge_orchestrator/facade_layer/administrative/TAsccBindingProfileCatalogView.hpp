#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
#include "assembler/communication_context/bindings/composition/TBindingOwnershipBoundary.hpp"

/**
 * @file TAsccBindingProfileCatalogView.hpp
 * @brief Administrative facade catalog of ASCC-supported binding profile families.
 *
 * Exposes binding profile capabilities to Pipeline Composer without leaking
 * mutable binding internals. It declares which handoff styles, cardinalities,
 * and ownership boundaries the ASCC component can advertise.
 *
 * It feeds `TAsccBindingAdmissionPolicy` and must not validate selected
 * bindings, open sessions, run protocols, or execute endpoints.
 */
namespace assembler::communication_context {
template <std::size_t Capacity>
struct TAsccBindingProfileCatalogView final {
    std::array<TBindingHandoffStyle, Capacity> handoff_styles{};
    std::array<TBindingCardinality, Capacity> cardinalities{};
    std::array<TBindingOwnershipBoundary, Capacity> ownership_boundaries{};
    std::size_t handoff_count{0u}, cardinality_count{0u}, ownership_count{0u};
    std::string_view catalog_name{"ascc_binding_profile_catalog"};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return handoff_count<=Capacity && cardinality_count<=Capacity && ownership_count<=Capacity && !catalog_name.empty(); }
    constexpr bool add_handoff_style(TBindingHandoffStyle v) noexcept { if(handoff_count>=Capacity||v==TBindingHandoffStyle::unknown) return false; handoff_styles[handoff_count++]=v; return true; }
    constexpr bool add_cardinality(TBindingCardinality v) noexcept { if(cardinality_count>=Capacity||v==TBindingCardinality::unknown) return false; cardinalities[cardinality_count++]=v; return true; }
    constexpr bool add_ownership_boundary(TBindingOwnershipBoundary v) noexcept { if(ownership_count>=Capacity||v==TBindingOwnershipBoundary::unknown) return false; ownership_boundaries[ownership_count++]=v; return true; }
    [[nodiscard]] constexpr bool supports_handoff_style(TBindingHandoffStyle v) const noexcept { for(std::size_t i=0;i<handoff_count;++i) if(handoff_styles[i]==v) return true; return false; }
    [[nodiscard]] constexpr bool supports_cardinality(TBindingCardinality v) const noexcept { for(std::size_t i=0;i<cardinality_count;++i) if(cardinalities[i]==v) return true; return false; }
};
}

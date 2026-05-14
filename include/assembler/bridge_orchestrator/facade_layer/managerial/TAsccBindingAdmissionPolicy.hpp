#pragma once
#include <string_view>
#include "assembler/communication_context/bindings/composition/TBindingCompositionMatcher.hpp"
#include "assembler/communication_context/bindings/session/TBindingSessionOpenProfile.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccBindingProfileCatalogView.hpp"
#include "assembler/communication_context/facade_layer/common/TAsccBindingEvidenceAdapter.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolBindingRequirement.hpp"
/**
 * @file TAsccBindingAdmissionPolicy.hpp
 * @brief Managerial facade policy for admitting a selected ASCC binding profile.
 *
 * Admits or rejects a selected binding profile using administrative catalog
 * support, composition matching, session-open readiness, role mapping, and
 * obligation-surface evidence. It does not execute endpoints.
 */
namespace assembler::communication_context {
struct TAsccBindingAdmissionPolicy final {
    template <std::size_t CatalogCapacity>
    [[nodiscard]] static constexpr TAsccBindingReadinessView admit(
        const TAsccBindingProfileCatalogView<CatalogCapacity>& catalog,
        TBindingHandoffStyle observed_handoff_style,
        TBindingCardinality observed_cardinality,
        bool session_available, bool bridge_available, bool protocol_available,
        TProtocolBindingRequirement requirement,
        TBindingSessionOpenProfile session_profile,
        bool role_map_ready, bool obligation_surfaces_ready,
        std::string_view note = {}) noexcept {
        const bool catalog_supports = catalog.supports_handoff_style(observed_handoff_style) && catalog.supports_cardinality(observed_cardinality);
        const auto composition = TBindingCompositionMatcher::match(observed_handoff_style, observed_cardinality, session_available, bridge_available, protocol_available, requirement, note);
        return TAsccBindingEvidenceAdapter::to_readiness_view(composition, session_profile, catalog_supports, role_map_ready, obligation_surfaces_ready, note);
    }
};
}

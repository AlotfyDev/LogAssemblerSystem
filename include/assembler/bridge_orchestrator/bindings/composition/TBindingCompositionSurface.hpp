#pragma once

#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionMetadata.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionReport.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionRequirement.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionView.hpp"
#include "assembler/communication_context/bindings/composition/TBindingExecutionAssumption.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
#include "assembler/communication_context/bindings/composition/TBindingOwnershipBoundary.hpp"

/**
 * @file TBindingCompositionSurface.hpp
 * @brief Aggregate surface for ASCC-COMP-W04 binding composition metadata.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_COMP_W04_BINDING_COMPOSITION_SURFACE_AVAILABLE = true;
}

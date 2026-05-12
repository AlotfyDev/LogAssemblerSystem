#pragma once

#include "assembler/communication_context/obligations/ports/TPort.hpp"

/**
 * @file TPort.hpp
 * @brief Compatibility forwarding header for the canonical host-side port obligation facade.
 *
 * @section ascc_comp_w01_reason ASCC-COMP-W01 Cleanup Reason
 * This file previously existed as an empty header while the implemented CRTP
 * host-side port obligation facade lived at:
 *
 * `assembler/communication_context/obligations/ports/TPort.hpp`
 *
 * In a header-only system an empty public/canonical-looking header is a
 * structural gap.  This forwarding header preserves include compatibility
 * while making the dependency explicit and non-empty.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This file does not define a second `TPort` type.  It forwards to the
 * canonical W05 obligation facade and must not introduce endpoint-domain
 * dependencies, bridge orchestration, runtime scheduling, or concrete port
 * implementations.
 */

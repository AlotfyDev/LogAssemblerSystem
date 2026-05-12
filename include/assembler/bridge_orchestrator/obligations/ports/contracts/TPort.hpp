#pragma once

#include "../TPort.hpp"

/**
 * @file TPort.hpp
 * @brief Compatibility forwarding header for the canonical host-side port obligation facade.
 *
 * @section ascc_comp_w01_reason ASCC-COMP-W01 Cleanup Reason
 * This file previously existed as an empty header while the implemented CRTP
 * host-side port obligation facade lived one level above this contracts path:
 *
 * `obligations/ports/TPort.hpp`
 *
 * In a header-only system an empty public/canonical-looking header is a
 * structural gap.  This forwarding header preserves include compatibility
 * while making the dependency explicit and non-empty.
 *
 * @section ascc_path_rule Path Rule
 * This header intentionally uses a local relative include instead of relying
 * on the unresolved `bridge_orchestrator` versus `communication_context` root
 * naming decision.  It therefore avoids creating a new dependency on a root
 * alias while W01 continues the full path audit.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This file does not define a second `TPort` type.  It forwards to the
 * canonical W05 obligation facade and must not introduce endpoint-domain
 * dependencies, bridge orchestration, runtime scheduling, or concrete port
 * implementations.
 */

#pragma once

#include "../TBridge.hpp"

/**
 * @file TBridge.hpp
 * @brief Compatibility forwarding header for the endpoint-neutral Bridge Core model orchestrator.
 *
 * @section ascc_comp_w01_reason ASCC-COMP-W01 Cleanup Reason
 * This file previously existed as an empty orchestration-path header while the
 * implemented W10 endpoint-neutral `TBridge<PlanCapacity>` lived one level
 * above this orchestration path:
 *
 * `bridge_core/TBridge.hpp`
 *
 * In a header-only ASCC core, empty canonical-looking headers are structural
 * gaps.  This forwarding header keeps the orchestration include path usable
 * without defining a duplicate bridge type.
 *
 * @section ascc_path_rule Path Rule
 * This header intentionally uses a local relative include instead of relying
 * on the unresolved `bridge_orchestrator` versus `communication_context` root
 * naming decision.  It therefore avoids creating a new dependency on a root
 * alias while W01 continues the full path audit.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This header does not introduce a concrete endpoint-invoking bridge runtime.
 * It forwards to the current model-step bridge core.  Endpoint invocation,
 * scheduling, plugin loading, and domain-specific integrations remain outside
 * this forwarding header and outside ASCC core cleanup scope.
 */

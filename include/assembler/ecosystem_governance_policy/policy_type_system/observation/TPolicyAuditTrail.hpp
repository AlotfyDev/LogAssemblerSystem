#pragma once

#include <vector>
#include "TPolicyAuditMarker.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAuditTrail.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyAuditTrail is a local in-memory collection of audit markers for policy observation. It provides a simple carrier for grouped markers without becoming persistent audit storage or a logging backend.
 *
 * Why this file exists in W05:
 *   W05 needs a way to group audit markers for later views and aggregate policy surfaces, while preserving that durable storage and export are out of scope.
 *
 * Relationship to previous waves:
 *   - W01 identity gives each marker a policy subject.
 *   - W04 lifecycle markers may later be represented as audit markers.
 *
 * Relationship to future waves:
 *   - W09 TPolicy may hold or expose an audit trail view.
 *   - W10 assignment may record assignment-related audit markers, but assignment remains later.
 *   - W11 registry may reference audit trails without owning observation semantics.
 *
 * Explicit non-responsibilities:
 *   TPolicyAuditTrail is not a database table, not a telemetry exporter, not a logging framework, not a registry, not a thread-safe event stream, and not a policy execution history engine.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

class TPolicyAuditTrail final
{
public:
    using marker_type = TPolicyAuditMarker;
    using container_type = std::vector<marker_type>;

    TPolicyAuditTrail() = default;

    void Add(marker_type marker)
    {
        markers_.push_back(marker);
    }

    [[nodiscard]] bool Empty() const noexcept { return markers_.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return markers_.size(); }
    [[nodiscard]] const container_type& Markers() const noexcept { return markers_; }

private:
    container_type markers_{};
};

} // namespace assembler::ecosystem_governance::policy_type_system

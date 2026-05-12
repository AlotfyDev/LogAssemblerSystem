#pragma once

/*
    LOGAPI-W02 — Content Profile And Schema Paths

    This header belongs to the Log Level API content-profile layer.

    Responsibility:
        Define content profile abstractions and schema path descriptors used by
        the configuration surface before the consuming hot path receives content.

    Boundary:
        This file must not define concrete JSON schemas, concrete C-style struct
        layouts, concrete validators, metadata struct implementation, timestamp
        stabilization algorithms, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Content schema paths are open and configurable.
        JSON and C-style struct primitive paths are separated.
        The consuming API receives content only and uses an already resolved
        active profile.
*/

#include <string>

#include "TLogApiCStyleStructPrimitiveProfileDescriptor.hpp"
#include "TLogApiContentProfileDescriptor.hpp"
#include "TLogApiContentProfileId.hpp"
#include "TLogApiContentProfileRegistryView.hpp"
#include "TLogApiContentProfileStatus.hpp"
#include "TLogApiJsonContentProfileDescriptor.hpp"

namespace assembler::log_level_api::content {

/*
    Configuration-time resolver for content profiles.

    This resolver resolves profile descriptors. It does not validate content and
    does not define concrete schema fields.
*/
class TLogApiContentProfileResolver final {
public:
    [[nodiscard]] static TLogApiContentProfileDescriptor MakeDefaultJsonProfile() {
        TLogApiJsonContentProfileDescriptor json{};
        TLogApiContentProfileDescriptor d{};
        d.id = TLogApiContentProfileId{1};
        d.status = TLogApiContentProfileStatus::Resolved;
        d.profile_name = json.profile_name;
        d.schema_path = json.ToPathDescriptor();
        d.validation_required = true;
        d.validator_binding_name = "default.json.validator.binding";
        return d;
    }

    [[nodiscard]] static TLogApiContentProfileDescriptor MakeDefaultCStyleStructPrimitiveProfile() {
        TLogApiCStyleStructPrimitiveProfileDescriptor cstyle{};
        TLogApiContentProfileDescriptor d{};
        d.id = TLogApiContentProfileId{2};
        d.status = TLogApiContentProfileStatus::Resolved;
        d.profile_name = cstyle.profile_name;
        d.schema_path = cstyle.ToPathDescriptor();
        d.validation_required = false;
        d.validator_binding_name = {};
        return d;
    }

    [[nodiscard]] static TLogApiContentProfileRegistryView MakeDefaultRegistryView() {
        TLogApiContentProfileRegistryView view{};
        view.profiles.push_back(MakeDefaultJsonProfile());
        view.profiles.push_back(MakeDefaultCStyleStructPrimitiveProfile());
        return view;
    }
};

} // namespace assembler::log_level_api::content

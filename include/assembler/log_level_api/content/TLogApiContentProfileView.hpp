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

#include "TLogApiContentProfileDescriptor.hpp"

namespace assembler::log_level_api::content {

struct TLogApiContentProfileView final {
    std::string profile_name{};
    std::string schema_path_name{};
    std::string schema_path_kind{};
    bool validation_required{false};
    bool ready_for_configuration_use{false};

    [[nodiscard]] static TLogApiContentProfileView From(const TLogApiContentProfileDescriptor& descriptor) {
        TLogApiContentProfileView view{};
        view.profile_name = descriptor.profile_name;
        view.schema_path_name = descriptor.schema_path.path_name;
        view.validation_required = descriptor.validation_required;
        view.ready_for_configuration_use = descriptor.IsReadyForConfigurationUse();

        if (descriptor.schema_path.IsJsonPath()) {
            view.schema_path_kind = "json";
        } else if (descriptor.schema_path.IsCStyleStructPrimitivePath()) {
            view.schema_path_kind = "c_style_struct_primitives";
        } else {
            view.schema_path_kind = "unknown";
        }

        return view;
    }
};

} // namespace assembler::log_level_api::content

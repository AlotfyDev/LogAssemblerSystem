#pragma once

/*
    LOGAPI-W06 — API Facade Content-Only Input

    This header belongs to the Log Level API consuming facade layer.

    Responsibility:
        Define the content-only API input surface and admission result carriers
        that consume a previously resolved active profile.

    Boundary:
        The API facade receives content only.
        It must not receive schema definitions, metadata struct definitions,
        validator bindings, timestamp stabilization rules, envelope assembly
        instructions, communication bindings, or policy assignment material with
        every payload.

    Doctrine:
        Configure first. Consume content only.
        The API facade uses an already resolved active profile.
*/

#include <string>

#include "TLogApiFacadeConfigRef.hpp"
#include "TLogApiFacadeId.hpp"
#include "TLogApiFacadeStatus.hpp"

namespace assembler::log_level_api::api_facade {

struct TLogApiFacadeView final {
    TLogApiFacadeId id{};
    TLogApiFacadeStatus status{TLogApiFacadeStatus::Unknown};
    std::string active_content_profile{};
    bool receives_content_only{true};
    bool ready{false};

    [[nodiscard]] static TLogApiFacadeView From(
        TLogApiFacadeId id,
        const TLogApiFacadeConfigRef& config
    ) {
        TLogApiFacadeView view{};
        view.id = id;
        view.status = config.IsReady() ? TLogApiFacadeStatus::Ready : TLogApiFacadeStatus::Rejected;
        view.ready = config.IsReady();
        if (config.active_profile != nullptr) {
            view.active_content_profile = config.active_profile->content_profile_name;
        }
        return view;
    }
};

} // namespace assembler::log_level_api::api_facade

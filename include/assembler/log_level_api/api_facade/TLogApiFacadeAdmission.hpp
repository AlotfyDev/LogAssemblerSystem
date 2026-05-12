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

#include "TLogApiContentOnlyInput.hpp"
#include "TLogApiFacadeConfigRef.hpp"

namespace assembler::log_level_api::api_facade {

/*
    Admission precheck for content-only API calls.

    Admission validates that the input contains content and that the facade has
    a resolved configuration context. It does not validate content schema rules.
*/
struct TLogApiFacadeAdmission final {
    [[nodiscard]] static bool CanAdmit(
        const TLogApiContentOnlyInput& input,
        const TLogApiFacadeConfigRef& config
    ) noexcept {
        return input.IsPresent() && config.IsReady();
    }
};

} // namespace assembler::log_level_api::api_facade

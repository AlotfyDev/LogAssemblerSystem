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

#include "TLogApiContentInputStatus.hpp"
#include "TLogApiContentOnlyInput.hpp"
#include "TLogApiFacadeAcceptedContent.hpp"
#include "TLogApiFacadeAdmission.hpp"
#include "TLogApiFacadeConfigRef.hpp"
#include "TLogApiFacadeInputResult.hpp"
#include "TLogApiFacadeIssue.hpp"

namespace assembler::log_level_api::api_facade {

/*
    Content-only facade.

    This facade admits content only. Everything else must already be resolved
    through configuration and referenced via TLogApiFacadeConfigRef.
*/
class TLogApiFacade final {
public:
    [[nodiscard]] static TLogApiFacadeInputResult AcceptContent(
        const TLogApiContentOnlyInput& input,
        const TLogApiFacadeConfigRef& config
    ) {
        TLogApiFacadeInputResult result{};

        if (!input.IsPresent()) {
            result.status = TLogApiContentInputStatus::Empty;
            result.issues.push_back({
                "LOGAPI_FACADE_CONTENT_EMPTY",
                "The Log Level API consuming facade requires content input.",
                true
            });
            return result;
        }

        if (!config.IsReady()) {
            result.status = TLogApiContentInputStatus::Rejected;
            result.issues.push_back({
                "LOGAPI_FACADE_CONFIG_NOT_READY",
                "The Log Level API facade requires a resolved active profile before consuming content.",
                true
            });
            return result;
        }

        result.status = TLogApiContentInputStatus::Accepted;
        result.accepted_content.content = input.content;
        result.accepted_content.active_profile = config.active_profile;
        return result;
    }
};

} // namespace assembler::log_level_api::api_facade

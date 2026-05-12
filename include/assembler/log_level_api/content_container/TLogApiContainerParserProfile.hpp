#pragma once

/*
    LOGAPI-W31 — Content Container Core And Batch Parse Model

    Responsibility:
        Define content container references, container shape descriptors,
        batch parse requests/results, parsed content batch references/views,
        and container envelope emission strategy descriptors.

    Boundary:
        This wave does not implement MT5-specific container parsers, JSON batch
        parsers, C-style struct batch parsers, validators, metadata injection,
        timestamp stabilization, envelope assembly, circulation handoff, policy
        assignment, or runtime dispatch.

    Doctrine:
        Container parser selection is configuration-time.
        Container parser execution is hot-path.
        A container parser handles one known container type.
        Element parser handles one known element type.
        No runtime parser dispatch inside the batch loop.
*/

#include <string>

#include "TLogApiContainerParserId.hpp"
#include "TLogApiContainerParserStatus.hpp"
#include "TLogApiContentContainerElementKind.hpp"
#include "TLogApiContentContainerKind.hpp"
#include "TLogApiContentContainerShape.hpp"

namespace assembler::log_level_api::content_container {

/*
    Container parser profile.

    This is resolved before the hot path. It binds one parser to one container
    kind and one element kind.
*/
struct TLogApiContainerParserProfile final {
    TLogApiContainerParserId id{};
    TLogApiContainerParserStatus status{TLogApiContainerParserStatus::Unknown};
    TLogApiContentContainerKind container_kind{TLogApiContentContainerKind::Unknown};
    TLogApiContentContainerElementKind element_kind{TLogApiContentContainerElementKind::Unknown};

    std::string parser_name{};
    std::string element_parser_name{};
    std::string supported_schema_name{};

    [[nodiscard]] bool IsResolved() const noexcept {
        return id.IsValid()
            && (status == TLogApiContainerParserStatus::Resolved
                || status == TLogApiContainerParserStatus::Active)
            && container_kind != TLogApiContentContainerKind::Unknown
            && element_kind != TLogApiContentContainerElementKind::Unknown
            && !parser_name.empty()
            && !element_parser_name.empty()
            && !supported_schema_name.empty();
    }

    [[nodiscard]] bool Matches(const TLogApiContentContainerShape& shape) const noexcept {
        return IsResolved()
            && shape.container_kind == container_kind
            && shape.element_kind == element_kind;
    }
};

} // namespace assembler::log_level_api::content_container

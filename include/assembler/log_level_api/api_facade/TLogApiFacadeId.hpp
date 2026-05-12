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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::api_facade {

struct TLogApiFacadeId final {
    std::uint64_t value{0};

    constexpr TLogApiFacadeId() = default;
    constexpr explicit TLogApiFacadeId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-facade-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::api_facade

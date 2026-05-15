#pragma once
#include <string_view>

/**
 * @file TIntegrationBoundaryExportContract.hpp
 * @brief Optional export contract for integration boundary profiles.
 *
 * This is a contract only. It does not implement file IO, database, telemetry,
 * network transfer, or logging.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryExportContract final {
        std::string_view export_family{};
        bool export_enabled{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !export_family.empty(); }
    };
}

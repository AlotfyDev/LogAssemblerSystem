#pragma once
#include <string_view>

/**
 * @file TDiagnosticExportReport.hpp
 * @brief Report describing an attempted diagnostic export through a boundary.
 */
namespace assembler::communication_context {
    struct TDiagnosticExportReport final {
        bool attempted{false};
        bool accepted{false};
        std::string_view export_family{};
        std::string_view note{};

        [[nodiscard]] constexpr bool succeeded() const noexcept {
            return attempted && accepted;
        }
    };
}

#pragma once
#include <cstddef>
#include <string_view>

/**
 * @file TParticipantCapabilityMatchReport.hpp
 * @brief Aggregate report for participant capability matching.
 */
namespace assembler::communication_context {
    struct TParticipantCapabilityMatchReport final {
        std::size_t total_required{0u};
        std::size_t matched_required{0u};
        std::size_t missing_required{0u};
        std::size_t optional_missing{0u};
        std::size_t mismatched{0u};
        std::string_view report_name{"participant_capability_match_report"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !report_name.empty(); }
        [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && missing_required == 0u && mismatched == 0u; }
    };
}

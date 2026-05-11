#pragma once
#include <cstdint>
#include <functional>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationCompatibilityReportId final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TCirculationCompatibilityReportId() noexcept = default;
    constexpr explicit TCirculationCompatibilityReportId(value_type input) noexcept : value(input) {}
    [[nodiscard]] static constexpr TCirculationCompatibilityReportId invalid() noexcept { return TCirculationCompatibilityReportId{k_invalid_value}; }
    [[nodiscard]] static constexpr TCirculationCompatibilityReportId from_raw(value_type input) noexcept { return TCirculationCompatibilityReportId{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] friend constexpr bool operator==(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return a.value == b.value; }
    [[nodiscard]] friend constexpr bool operator!=(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return !(a == b); }
    [[nodiscard]] friend constexpr bool operator<(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return a.value < b.value; }
    [[nodiscard]] friend constexpr bool operator<=(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return a.value <= b.value; }
    [[nodiscard]] friend constexpr bool operator>(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return b < a; }
    [[nodiscard]] friend constexpr bool operator>=(TCirculationCompatibilityReportId a, TCirculationCompatibilityReportId b) noexcept { return b <= a; }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

namespace std {
template<> struct hash<assembler::circulation_mechanism::versioning::TCirculationCompatibilityReportId> {
    std::size_t operator()(const assembler::circulation_mechanism::versioning::TCirculationCompatibilityReportId& input) const noexcept {
        return std::hash<assembler::circulation_mechanism::versioning::TCirculationCompatibilityReportId::value_type>{}(input.raw());
    }
};
}

#pragma once
#include <cstdint>
#include <functional>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationProfileVersion final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TCirculationProfileVersion() noexcept = default;
    constexpr explicit TCirculationProfileVersion(value_type input) noexcept : value(input) {}
    [[nodiscard]] static constexpr TCirculationProfileVersion invalid() noexcept { return TCirculationProfileVersion{k_invalid_value}; }
    [[nodiscard]] static constexpr TCirculationProfileVersion from_raw(value_type input) noexcept { return TCirculationProfileVersion{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] friend constexpr bool operator==(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return a.value == b.value; }
    [[nodiscard]] friend constexpr bool operator!=(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return !(a == b); }
    [[nodiscard]] friend constexpr bool operator<(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return a.value < b.value; }
    [[nodiscard]] friend constexpr bool operator<=(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return a.value <= b.value; }
    [[nodiscard]] friend constexpr bool operator>(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return b < a; }
    [[nodiscard]] friend constexpr bool operator>=(TCirculationProfileVersion a, TCirculationProfileVersion b) noexcept { return b <= a; }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

namespace std {
template<> struct hash<assembler::circulation_mechanism::versioning::TCirculationProfileVersion> {
    std::size_t operator()(const assembler::circulation_mechanism::versioning::TCirculationProfileVersion& input) const noexcept {
        return std::hash<assembler::circulation_mechanism::versioning::TCirculationProfileVersion::value_type>{}(input.raw());
    }
};
}

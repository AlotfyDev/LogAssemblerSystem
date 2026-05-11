#pragma once
#include <cstdint>
#include <functional>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationSchemaVersion final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TCirculationSchemaVersion() noexcept = default;
    constexpr explicit TCirculationSchemaVersion(value_type input) noexcept : value(input) {}
    [[nodiscard]] static constexpr TCirculationSchemaVersion invalid() noexcept { return TCirculationSchemaVersion{k_invalid_value}; }
    [[nodiscard]] static constexpr TCirculationSchemaVersion from_raw(value_type input) noexcept { return TCirculationSchemaVersion{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] friend constexpr bool operator==(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return a.value == b.value; }
    [[nodiscard]] friend constexpr bool operator!=(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return !(a == b); }
    [[nodiscard]] friend constexpr bool operator<(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return a.value < b.value; }
    [[nodiscard]] friend constexpr bool operator<=(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return a.value <= b.value; }
    [[nodiscard]] friend constexpr bool operator>(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return b < a; }
    [[nodiscard]] friend constexpr bool operator>=(TCirculationSchemaVersion a, TCirculationSchemaVersion b) noexcept { return b <= a; }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler

namespace std {
template<> struct hash<assembler::circulation_mechanism::versioning::TCirculationSchemaVersion> {
    std::size_t operator()(const assembler::circulation_mechanism::versioning::TCirculationSchemaVersion& input) const noexcept {
        return std::hash<assembler::circulation_mechanism::versioning::TCirculationSchemaVersion::value_type>{}(input.raw());
    }
};
}

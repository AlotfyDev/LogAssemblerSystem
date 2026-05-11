#pragma once
#include <cstdint>
#include <functional>

/*
    TContainerRegistryIndex.hpp

    Local dependency for CME-CONTAINER-REGISTRY-PROD-W01.

    Responsibility:
        One-based index locator into TContainerRegistry.

    Non-ownership:
        Does not own the container, does not prove lifetime, and must not be
        exposed as an external mutable pointer.
*/

namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryIndex final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};

    constexpr TContainerRegistryIndex() noexcept = default;
    constexpr explicit TContainerRegistryIndex(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TContainerRegistryIndex invalid() noexcept { return TContainerRegistryIndex{k_invalid_value}; }
    [[nodiscard]] static constexpr TContainerRegistryIndex from_raw(value_type v) noexcept { return TContainerRegistryIndex{v}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] constexpr value_type one_based() const noexcept { return value; }
    [[nodiscard]] constexpr value_type zero_based_or(value_type fallback) const noexcept { return is_valid() ? value - 1U : fallback; }

    [[nodiscard]] friend constexpr bool operator==(TContainerRegistryIndex a, TContainerRegistryIndex b) noexcept { return a.value == b.value; }
    [[nodiscard]] friend constexpr bool operator!=(TContainerRegistryIndex a, TContainerRegistryIndex b) noexcept { return !(a == b); }
};
} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template<> struct hash<assembler::circulation_mechanism::TContainerRegistryIndex> {
    std::size_t operator()(const assembler::circulation_mechanism::TContainerRegistryIndex& x) const noexcept {
        return std::hash<assembler::circulation_mechanism::TContainerRegistryIndex::value_type>{}(x.raw());
    }
};
}
